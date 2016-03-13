<?php
    /*************************************************************************
     * index.php
     * 
     * Computer Science 50
     * Problem Set 7
     *
     * CONTROLLER FOR BEHAVIOR OF THIS WEBSITE
     *
     * Masatoshi Nishiguchi
     * nishiguchi.masa@gmail.com
     *************************************************************************/
    
    // configuration
    require("../includes/config.php"); 

    
    // PREPARE DATA FOR PORTFOLIO
    // ==========================
    
    // data envelope
    $positions = [];
     
    // get all the symbols existing in database
    $rows = query("SELECT symbol, shares FROM portfolio WHERE id = ?", $_SESSION["id"]);
    
    // if no symbol exsists in database
    if (count($rows) == 0)
    {
        $positions[] = [
                "symbol" => "-",
                "name" => "-",    
                "shares" => 0,
                "price" => 0,
                "total" => 0,
        ];
    }
    else
    {
        // iterate for each row
        foreach ($rows as $row)
        {
            // get name and current price for each symbol
            $stock = lookup($row["symbol"]);
                
            if ($stock !== false)
            {
                $positions[] = [
                    "name" => $stock["name"],
                    "price" => $stock["price"],
                    "symbol" => $row["symbol"],
                    "shares" => $row["shares"],
                    "total" => $stock["price"] * $row["shares"],
                ];
            }
        }
    }
      
    // search for a user’s current cash balance
    $balance = query("SELECT cash FROM users WHERE id = {$_SESSION["id"]}");
    $cash = $balance[0]["cash"];
    
    // calculate total asset
    $asset = $cash;
    
    foreach ($positions as $position)
    {
        $asset += $position["total"];
    }

     
    // RENDER PORTFOLIO
    // ================
    
    render("portfolio.php", ["positions" => $positions, "cash" => $cash, "asset" => $asset, "title" => "Portfolio"]);

?>
