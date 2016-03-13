                
                <ul class="nav nav-pills">
                    <li><a href="quote.php">Quote</a></li>
                    <li><a href="buy.php">Buy</a></li>
                    <li><a href="sell.php">Sell</a></li>
                    <li><a href="history.php">History</a></li>
                    <li><a href="logout.php"><strong>Log Out</strong></a></li>
                </ul>

                <table class="table table-striped">

                    <thead>
                        <tr>
                            <th>Symbol</th>
                            <th>Name</th>
                            <th class="number">Shares</th>
                            <th class="number">Price</th>
                            <th class="number">TOTAL</th>
                        </tr>
                    </thead>

                    <tbody>

                        <?php foreach ($positions as $position): ?>

                        <tr>
                            <td><?= $position["symbol"] ?></td>
                            <td><?= $position["name"] ?></td>
                            <td class="number"><?= $position["shares"] ?></td>
                            <td class="number"><?= number_format($position["price"], 2) ?></td>
                            <td class="number"><?= number_format($position["total"], 2) ?></td>
                        </tr>

                        <?php endforeach; ?> 
                        
                        <tr>    
                            <td class="number" colspan="4"><strong>Cash on hand</strong></td>
                            <td class="number">$<?= number_format($cash, 2) ?></td>
                        </tr>
                        
                        <tr>    
                            <td class="number" colspan="4"><strong>TOTAL ASSET</strong></td>
                            <td class="number">$<?= number_format($asset, 2) ?></td>
                        </tr>
                        
                    </tbody>

                </table>           
            
