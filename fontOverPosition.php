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
                    <form method="get" action="switch_toFunction_fontOverlay.php">
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

                                                                     ?>" id="photoSelectedOne" name="photoSelectedOne"/>

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
                            <input  type="text" id="fontString" name="fontString"  maxlength="16" class="form-input"/>
                            <div class="columns">
                                <div class="column col-6">
                                    <label class="form-label">Effects so far</label>
                                    <select type="select" id="effectsChosen" name="effectsChosen" class="form-select">
                                        <option value="None">None</option>
                                        <option value="fontOverlaySingle">fontOverlaySingle</option>
                                        <option value="fontOverlayShade">fontOverlayShade</option>
                                        <option value="fontOverlayShadeTransparent">fontOverlayShadeTransparent</option>
                                        <option value="fontContrastColor_basic">fontContrastColor_basic</option>
                                        <option value="fontContrastColor_hue">fontContrastColor_hue</option>
                                        <option value="contrastWatermark">contrastWatermark</option>
                                        <option value="randomFontOverlay">randomFontOverlay</option>
                                        <option value="randomFontOverlayWithRandomGradient">randomFontOverlayWithRandomGradient</option>
                                        <option value="fontOverlaySingleRandomColor">fontOverlaySingleRandomColor</option>
                                        <option value="fontOverlayMultipleShade">fontOverlayMultipleShade</option>
                                        <option value="fontOverlay3D_primaryColor">fontOverlay3D_primaryColor</option>
                                        <option value="fontOverlay_secondaryColor">fontOverlay_secondaryColor</option>
                                    </select>

                                </div>
                            </div>
                        </div>




                        </div>

                <div class="column col-3">
                </div>
                </div>
            </div>


        </div>
    </body>
</html>

