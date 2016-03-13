<?php

    /*************************************************************************
     * sell.php
     * CONTROLLER FOR SELLING STOCKS
     *************************************************************************/
     
    // configuration
    require("../includes/config.php");
    
    
    // if sell_form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {   
        // VALIDATE SUBMISSION
        // ===================
        
        // if no symbol was selected
        if ($_POST["symbol"] == '\0')
        {   
            apologize("You must select a stock to sell.");
        }
        
        // SELLING
        // =======
        
        // check current price of selected stock
        $stock = lookup($_POST["symbol"]);        
        $price = $stock["price"];
        
        // check for currently holding shares
        $data = query("SELECT shares FROM portfolio  WHERE id = ? AND symbol = ?", 
                $_SESSION["id"], $_POST["symbol"]);
        
        $shares = $data[0]["shares"]; 
              
        // remove selected stock from database
        query("DELETE FROM portfolio WHERE id = ? AND symbol = ?", 
                $_SESSION["id"], $_POST["symbol"]);
               
        // update cash amount
        query("UPDATE users SET cash = cash + ? WHERE id = ?", 
                $price * $shares, $_SESSION["id"]);

        
        // UPDATE HISTORY
        // ==============
        
        query("INSERT INTO history(id, transaction, symboL, shares, price) VALUES(?,?,?,?,?)", 
                $_SESSION["id"], "SELL", $_POST["symbol"], $shares, $price);
        
   
        // REDIRECT TO PORTFOLIO
        // =====================
        redirect("/");  
    }
    else
    {
        // PREPARE DATA FOR SELL_FORM
        // ==========================
        
        // get symbols existing in database
        $rows = query("SELECT symbol FROM portfolio WHERE id = {$_SESSION["id"]}");
        
        // if no symbol exsists in database
        if (count($rows) == 0)
        {
            apologize("You have no stock to sell.");
        }
  
        // create array to store symbols
        for($i = 0; $i < sizeof($rows); $i++)
        {
            $symbols[$i] = $rows[$i]["symbol"];
        } 
       
        
        // RENDER SELL_FORM
        // ================
        
        render("sell_form.php", ["symbols" => $symbols, "title" => "Sell"]);
    }
?>    

