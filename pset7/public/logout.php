<?php
    /*************************************************************************
     * logout.php
     * 
     * Computer Science 50
     * Problem Set 7
     *
     * CONTROLLER FOR LOGOUT
     *
     * Masatoshi Nishiguchi
     * nishiguchi.masa@gmail.com
     *************************************************************************/
    
    // configuration
    require("../includes/config.php"); 

    // log out current user, if any
    logout();

    // redirect user
    redirect("/");

?>
