<?php

$fileString="./src-img/tableDisplay/".$photoSelectedOne;
$size=getimagesize($fileString);
$var1=preg_split("/[\/]/",$fileString);
$filesInFontArray=scandir("./src-misc/");


?>



<!DOCTYPE html>
<html lang="en"> 
    <head>
        <link rel="stylesheet" href="src-css/spectre_bartleDoo.css">
        <meta charset="utf-8"/>
    </head>
    <body>
        
        <div class="container">



            
            <div class="columns">
                <div class="column col-3">
                </div>
                <div class="column col-6">
                    <h2>Dear God, not another table</h2>
                    <form method="get" action="trackCoordinate.php">
                        <table class="table table-striped">
                            <tr>
                                <th width="70%">Actual photo image</th>
                                <th>Some details</th>

                            </tr>
                            <tr>
                                
                                <td>

                                    <input type="image" alt="some text when things go wrong" src="<?php
                                                                                                  echo $fileString;
                                                                                                  ?>" name="fontOverImage" />
                                    <input hidden type="text" value="<?php
                                                                     echo $photoSelectedOne;

                                                                     ?>" id="fileString" name="fileString"/>

                                </td>
                                <td>
                                    <label class="form-label">File name: <?php
                                                                         echo $var1[sizeof($var1)-1];

                                                                         ?></label>
                                    <label class="form-label">Width: <?php
                                                                     echo $size[0];
                                                                     ?></label>
                                    <label class="form-label">Height: <?php
                                                                      echo $size[1];
                                                                      ?></label>
                                    <label class="form-label">Image Type: png (PNG)</label>
                                    
                                    

                                </td>
                            </tr>
                            
                            
                        </table>
                        
                        <div class="columns">
                            

                        <div class="column col-6">
                            <label class="form-label">Font available in directory:</label>
                            <select id="fontSelected" name="fontSelected" class="form-select">
                                <?php
                                foreach ($filesInFontArray as $files){
                                    if(preg_match('/(ttf)/',$files)){
                                        echo "<option>";
                                        echo $files;
                                        echo "</option>";
                                    }
                                }

                                ?>
                            </select>
                        </div>
                        <div class="column col-6">
                            <label class="form-label">Enter font string:</label>
                            <input  type="text" id="fontString" name="fontString"  maxlength="16"/>
                        </div>
                        
                        

                    </form>
                        </div>

                <div class="column col-3">
                </div>
                </div>
            </div>


        </div>
    </body>
</html>

