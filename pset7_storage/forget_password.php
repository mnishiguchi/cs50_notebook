<?php
    /*************************************************************************
     * forget_password.php
     * 
     * Computer Science 50
     * Problem Set 7
     *
     * CONTROLLER FOR HANDLING FORGOTTEN PASSWORD
     *
     * Masatoshi Nishiguchi
     * nishiguchi.masa@gmail.com
     *************************************************************************/
   
    // configuration
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // some form is submitted but username is not authenticated yet

        // VALIDATE SUBMISSION
        // ===================
                
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        elseif (empty($_POST["email"]))
        {
            apologize("You must provide your e-mail.");
        }
       
        // USER AUTHENTICATION
        // ===================
                
        // query database for user data set
        $rows = query("SELECT * FROM users WHERE username = ?", $_POST["username"]);

        // check if we found username in database
        if (count($rows) == 1)
        {
            // remember forget_password_form is completed
            $_SESSION["forget_password"]["username"] = true;
        }
        else
        {
            apologize("Invalid username");
        }
               
        // VERIFY USER BY EMAIL
        // ====================
        $subject = "C$50 Finance :: Reset Password"; 
        $message = "pset7/changepassword.php";
                                     
        // send email
        $issent = mail($_POST["email"], $subject, $message);
        if ($issent == true)
        {
            // remember email is sent
            $_SESSION["forget_password"]["email"] = true;
            apologize("OK");
        }
        else
        {
            apologize("FAILED");
        }

     
    }
    else
    {
        // RENDER FORGET PASSWORD FORM
        // ===========================
                        
        render("forget_password_form.php", ["title" => "Forget Password Form"]);
    }
?>
