<?php

// ------------ things to clean in this code ------------
// the last <div> structure may not be necessary
// gather all if/else conditional into 1 group

// ------------ things to clean in this code ------------

$photoSelectedOne=$_GET['photoSelectedOne'];

$fileString="./src-img/tableDisplay/".$photoSelectedOne;
$size=getimagesize($fileString);
$fileName=preg_split("/[\/]/",$fileString);
$filesInFontArray=scandir("./src-misc/");


if(!isset($_GET['coordinateArrays'])){
    $coordinateArrays=[];
    $counterArray=0;
}
else{
    $coordinateArrays=$_GET['coordinateArrays'];
    $counterArray=$_GET['counterArray'];
    $counterArray++;
}
if(isset($_GET['fontOverImage_x'])){
    array_push($coordinateArrays,$_GET['fontOverImage_x'],$_GET['fontOverImage_y']);
}


if($counterArray<10){
    $targetFile="./multipleCoordinate.php";
}else
$targetFile="./switch_toFunction_multipleCoordinates.php";






?>


<!DOCTYPE html>
<html lang="en"> 
    <head>
        <link rel="stylesheet" href="src-css/spectre-0.5.8/dist/spectre_bartleDoo.css">
        <meta charset="utf-8"/>
    </head>
    <body>

        <div class="container">



            <div class="columns">
                <div class="column col-3">
                </div>
                <div class="column col-6">
                    <h2>Dear God, not another table</h2>

                    <form method="get" action="<?php echo $targetFile; ?>">

                        <table class="table table-striped">
                            <tr>
                                <th width="70%">Actual photo image</th>
                                <th>Some details</th>

                            </tr>
                            <tr>

                                <td>

                                    <input type="image" <?php if($counterArray>9)echo "disabled"; ?> alt="some text when things go wrong" src="<?php
                                                                                                                                               echo $fileString;
                                                                                                                                               ?>" name="fontOverImage" />
                                    <input hidden type="text" value="<?php
                                                                     echo $photoSelectedOne;

                                                                     ?>" id="photoSelectedOne" name="photoSelectedOne"/>
                                    <?php
                                    if($counterArray>9){
                                        echo "
                            <input type='submit'  class='btn btn-primary' value='Generate effect' />
                                        ";
                                    }

                                    ?>

                                </td>
                                <td>
                                    <label class="form-label">File name: <?php
                                                                         echo $fileName[sizeof($fileName)-1];

                                                                         ?></label>
                                    <label class="form-label">Width: <?php
                                                                     echo $size[0];
                                                                     ?></label>
                                    <label class="form-label">Height: <?php
                                                                      echo $size[1];
                                                                      ?></label>
                                    <label class="form-label">Image Type: png (PNG)</label>

                                    <input hidden name="multipleInitiliazed" value="true" />
                                    <input hidden name="counterArray" value="<?php echo $counterArray;
                                                                             ?>" />

                                    <select hidden name="coordinateArrays[]" multiple>

                                        <?php
                                        foreach($coordinateArrays as $item){
                                            echo "<option value='";
                                            echo $item;
                                            echo "' selected></option>";
                                        }
                                        ?>
                                    </select>

                                    <div class="mt-2 pt-2">
                                        x and y coordinates:
                                        <ul class="sheep">

                                            <?php
                                            for($i=0;$i<sizeof($coordinateArrays);$i++){
                                                if($i%2==0){
                                                    echo "<li> <b>x</b>: ";
                                                    echo $coordinateArrays[$i];
                                                }else{
                                                    echo " <b>y</b>: ";
                                                    echo $coordinateArrays[$i];
                                                    echo "</li>";
                                                }

                                            }
                                            ?>
                                            <li></li>
                                        </ul>
                                    </div>
                                </td>



                            </tr>


                        </table>
                        
                        
                    </form>
                <div class="column col-3">
                </div>
                </div>
            </div>


        </div>
    </body>
</html>

