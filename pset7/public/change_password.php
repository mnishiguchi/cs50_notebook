<?php
    /*************************************************************************
     * change_password.php
     * 
     * Computer Science 50
     * Problem Set 7
     *
     * CONTROLLER FOR CHANGING PASSWORD
     *
     * Masatoshi Nishiguchi
     * nishiguchi.masa@gmail.com
     *************************************************************************/
   
    // configuration
    require("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // some form is submitted but not logged in yet
        if (!isset($_SESSION["change_password"]) || empty($_SESSION["id"]))
        {

            // VALIDATE SUBMISSION (FORM #1)
            // =============================
                
            if (empty($_POST["username"]))
            {
                apologize("You must provide your username.");
            }
            elseif (empty($_POST["password"]))
            {
                apologize("You must provide your password.");
            }


            // USER AUTHENTICATION
            // ===================
                
            // query database for user data set
            $rows = query("SELECT * FROM users WHERE username = ?", $_POST["username"]);

            // if we found user, check password
            if (count($rows) == 1)
            {
                // first (and only) row
                $row = $rows[0];

                // compare hash of user's input against hash that's in database
                if (crypt($_POST["password"], $row["hash"]) == $row["hash"])
                {
                    // remember that user's now logged in
                    $_SESSION["id"] = $row["id"];
                        
                    // remember form #1 is completed
                    $_SESSION["change_password"]["form_1"] = true;


                    // RENDER FORM #2 (new password)
                    // =============================
                
                    render("change_password_form_2.php", ["title" => "Change Password Form 2"]);
                }
            }

            // else notify user with error
            apologize("Invalid username and/or password.");
        }
    
        // Some form is submitted and user is authenticated already
        elseif (isset($_SESSION["id"]) && ($_SESSION["change_password"]["form_1"] == true))
        {
            // VALIDATE SUBMISSION (FORM #2)
            // ============================       
                        
            if (empty($_POST["new_password"]))
            {
                apologize("You must provide your new password.");
            }
            // if "password" does not equal "confirmation"
            elseif ($_POST["new_password"] !== $_POST["confirmation"]) 
            {
                apologize("Those passwords did not match.");
            }
     
            // UPDATE USER PASSWORD IN DATABASE
            //=================================
                
            // UPDATE `users` SET `hash`=[value-3], WHERE id =
            query("UPDATE users SET hash = ? WHERE id = ?",         
                    crypt($_POST["new_password"]), $_SESSION["id"]);


            // REDIRECT TO PORTFOLIO
            // =====================
                $_SESSION["change_password"] = [];  
                redirect("/");
        }
    }
    // if no form was submitted
    elseif (!isset($_SESSION["change_password"]) || empty($_SESSION["id"]))
    {
        // RENDER FORM #1 (username, old password)
        // =======================================
        
        render("change_password_form_1.php", ["title" => "Change Password Form 1"]);
    }
    // if form #1 is authenticated already 
    else
    {
        // RENDER FORM #2 (new password)
        // =============================
                    
        render("change_password_form_2.php", ["title" => "Change Password Form 2"]);
    }
?>
