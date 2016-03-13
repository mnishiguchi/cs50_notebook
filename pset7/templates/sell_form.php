
                <form action="sell.php" method="post">
                    <fieldset>
                    
                        <div class="form-group">  
                            <select class="form-control" name="symbol">
                                         
                                <option value='\0'>(select)</option>
                                
                                <?php foreach ($symbols as $symbol): ?>
                                <option value="<?=$symbol?>"><?=$symbol?></option>
                                <?php endforeach; ?>
                  
                            </select>  
                        </div>
                        
                        <div class="form-group">
                            <button type="submit" class="btn btn-primary btn-lg">Sell</button>
                        </div>
                        
                    </fieldset>     
                </form>

