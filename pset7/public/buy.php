<?php
    /*************************************************************************
     * buy.php
     * 
     * Computer Science 50
     * Problem Set 7
     *
     * CONTROLLER FOR BUYING STOCKS
     *
     * Masatoshi Nishiguchi
     * nishiguchi.masa@gmail.com
     *************************************************************************/
     
    // configuration
    require("../includes/config.php");
    
    
    // if buy_form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {   
        
        // VALIDATE SUBMISSION
        // ===================
        
        // ensure that user inputted symbol
        if ($_POST["symbol"] == '')
        {
            apologize("You must specify a stock to buy.");
        }
        
        // check if inputted symbol is valid 
        // (lookup ensures that symbol neither starts with ^ nor contains commas)
        if(!$stock = lookup($_POST["symbol"]))
        {
            apologize("Symbol not found.");
        }
        
        if ($_POST["shares"] == '')
        {
            apologize("You must specify a number of shares.");
        }

        // ensure that inputted number for shares is a non-negative integer
        if (preg_match("/^\d+$/", $_POST["shares"]) != true)    
        {
            apologize("Invalid number of shares.");
        }


        // ENSURE USER CAN AFFORD
        // ======================
        
        // current price of specified stock
        $price = $stock["price"];
          
        // estimated cost
        $cost = $price*$_POST["shares"];
         
        // cash on hand
        $data = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $cash_on_hand = $data[0]["cash"];

        // ensure user can afford the specified stock
        if ($cash_on_hand < $cost)
        {
            apologize("You cannot afford that.");
        }


        // UPDATE DATABASE
        // ===============

        // convert to uppercase all the characters in symbol
        $symbol = strtoupper($_POST["symbol"]);
        
        // insert stock to portfolio
        // or update the stock data if id-symbol pair already exists
        query("INSERT INTO portfolio (id, symbol, shares) VALUES(?,?,?)
            ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", 
                $_SESSION["id"], $symbol, $_POST["shares"]);
        
        // update cash
        query("UPDATE users SET cash = ? WHERE id = ?", $cash_on_hand - $cost, $_SESSION["id"]);
        
        
        // UPDATE HISTORY
        // ==============
        
        query("INSERT INTO history(id, transaction, symboL, shares, price) VALUES(?,?,?,?,?)", 
                $_SESSION["id"], "BUY", $symbol, $_POST["shares"], $price);
        

        // REDIRECT TO PORTFOLIO
        // =====================
        redirect("/"); 
              
    }  
    // if buy_form is not submitted yet
    else
    {
        
        // RENDER BUY_FORM
        // ===============
        
        render("buy_form.php", ["title" => "Buy"]);
    }
?>    

