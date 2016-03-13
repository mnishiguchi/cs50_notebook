<?php

    /**
     * config.php
     *
     * Computer Science 50
     * Problem Set 7
     *
     * Configures pages.
     */
     
    // enable display of all errors, warnings and notices
    ini_set("display_errors", true);       


    // requirements
    require("constants.php");
    require("functions.php");
    
    
    // enable sessions 
    session_start();    // to remember a user is logged in. 
    
    
    // authentication
    // if currently executing file is not login.php, logout.php, register.php etc
    if (!preg_match("{(?:login|logout|register|change_password|forget_password)\.php$}", $_SERVER["PHP_SELF"]))
    {
        // if id is not set yet
        if (empty($_SESSION["id"]))
        {
            redirect("login.php");    // require authentication
        }
    }

?>
