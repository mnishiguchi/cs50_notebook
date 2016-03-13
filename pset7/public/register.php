<?php
    /*************************************************************************
     * register.php
     * 
     * Computer Science 50
     * Problem Set 7
     *
     * CONTROLLER FOR USER REGISTRATION
     *
     * Masatoshi Nishiguchi
     * nishiguchi.masa@gmail.com
     *************************************************************************/
     
    // configuration
    require("../includes/config.php");
    
    
    // if register_form was submitted
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
        // if "password" does not equal "confirmation"
        else if ($_POST["password"] !== $_POST["confirmation"]) 
        {
            apologize("Those passwords did not match.");
        }
        
        // check if username is available
        $data = query("SELECT username FROM users WHERE username = ?", $_POST["username"]);
        
        if ((strcmp(strtoupper($data[0]["username"]), strtoupper($_POST["username"]))) == 0)
        {
            apologize("That username appears to be taken.");
        }


        // INSERT NEW USER INTO DATABASE
        //==============================
        
        query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)",
                $_POST["username"],          
                crypt($_POST["password"]));
        
        
        // LOG IN USER AUTOMATICALLY
        // =========================
        
        // find out user's id in database
        $rows = query("SELECT LAST_INSERT_ID() AS id");    
        
        // first (and only) row
        $id = $rows[0]["id"];

        // store user's ID in session
        $_SESSION["id"] = $id;

            
        // REDIRECT TO PORTFOLIO
        // =====================
            
        redirect("/");
 
    }
    // if register_form is not submitted yet
    else
    {
        // RENDER REGSTER_FORM
        // ===================
        
        render("register_form.php", ["title" => "Register"]);
    }
?>
