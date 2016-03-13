
                <table class="table table-striped">

                    <thead>
                        <tr>
                            <th>Transaction Type</th>
                            <th>Date/Time</th>
                            <th>Symbol</th>
                            <th class="number">Shares</th>
                            <th class="number">Price</th>
                        </tr>
                    </thead>

                    <tbody>        
                    <?php foreach ($positions as $position): ?>
                        <tr>
                            <td><?= $position["transaction"] ?></td>
                            <td><?= $position["date"] ?></td>
                            <td><?= $position["symbol"] ?></td>
                            <td class="number"><?= $position["shares"] ?></td>
                            <td class="number">$<?= number_format($position["price"], 2) ?></td>
                        </tr>
                    <?php endforeach; ?>    
                    </tbody>
                     
                </table> 
      
