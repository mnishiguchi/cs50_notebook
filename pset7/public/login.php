<?php
    /*************************************************************************
     * login.php
     * 
     * Computer Science 50
     * Problem Set 7
     *
     * CONTROLLER FOR USER AUTHENTICATION
     *
     * Masatoshi Nishiguchi
     * nishiguchi.masa@gmail.com
     *************************************************************************/
       
    // configuration
    require("../includes/config.php"); 


    // if login_form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        
        // VALIDATE SUBMISSION
        // ===================
        
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        else if (empty($_POST["password"]))
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


                // REDIRECT TO PORTFOLIO
                // =====================
                
                redirect("/");    
            }
        }

        // else notify user with error
        apologize("Invalid username and/or password.");
    }
    
    // if login_form is not submitted yet
    else 
    {
        // RENDER REGSTER_FORM
        // ===================
        
        render("login_form.php", ["title" => "Log In"]);
    }

?>
