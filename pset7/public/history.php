<?php
    /*************************************************************************
     * history.php
     * 
     * Computer Science 50
     * Problem Set 7
     *
     * CONTROLLER FOR LOGGING TRANSACTION
     *
     * Masatoshi Nishiguchi
     * nishiguchi.masa@gmail.com
     *************************************************************************/
    
    // configuration
    require("../includes/config.php"); 

    
    // PREPARE DATA FOR HISTORY
    // ========================
    
    // get history data from database
    $rows = query("SELECT transaction, date, symbol, shares, price FROM history WHERE id = ? 
                    ORDER BY date DESC LIMIT 25", $_SESSION["id"]);      
    
    // data envelope
    $positions = [];
    
    // if any symbols exsist in database
    if ($rows !== false) 
    {
        // put data in storage
        $positions = $rows;
    }


    // RENDER HISTORY_DISPLAY
    // ======================
    
    render("history_display.php", ["positions" => $positions, "title" => "History Display"]);

?>
