<?php
    /*************************************************************************
     * quote.php
     * 
     * Computer Science 50
     * Problem Set 7
     *
     * CONTROLLER FOR LOOKING UP QUOTES FOR INDIVIDUAL STOCKS
     *
     * Masatoshi Nishiguchi
     * nishiguchi.masa@gmail.com
     *************************************************************************/
    
    // configuration
    require("../includes/config.php");     
 
 
    // if quote_form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        
        // GET STOCK DATA
        // ==============
        
        $stock = lookup($_POST["symbol"]);  // returns assoc array with three keys("symbol", "name", "price")
        
        if ($stock !== false)
        {
            /* quote data format : "DVN.V","DISCOVERY VENTURE",0.17 */
            
            // store quote data in session
            $_SESSION["quote"] = $stock;
  
            
            // RENDER QUOTE_DISPLAY
            // ====================
               
            render("quote_display.php", ["title" => "Quote Display"]);
        }
        else
        {
            // else notify user with error
            apologize("Symbol not found.");
        }
    }
    // if quote_form is not submitted yet
    else    
    {   
        // RENDER QUOTE_FORM
        // =================
               
        render("quote_form.php", ["title" => "Quote Form"]);
    }  
?>
