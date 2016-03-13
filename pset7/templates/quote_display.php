 <div class="jumbotron">
                <?php
                    printf("<h3>A share of <h2>%s (%s)</h2><h3> costs </h3>",
                        $_SESSION["quote"]["name"], $_SESSION["quote"]["symbol"]); 
                ?>     
                <h2>$<?= number_format($_SESSION["quote"]["price"], 2); ?></h2>
                
                <h4>
                    <?php
                        printf('<a href="http://finance.yahoo.com/echarts?s=%s+Interactive#symbol=%s;range=1d"/>' ,
                         $_SESSION["quote"]["symbol"], $_SESSION["quote"]["symbol"]); 
                    ?>
                    more data</a> of this company
                </h4>
</div>
