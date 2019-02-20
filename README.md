# CrazyEffectsImageFilterPublic

This is web interface that applies a variety of image effects, created from the php GD functions, and applied to a set of 
jpeg images inside a local folder. the highlight of the effects are the cloud effects function, which allow the users to set the cloud's weight and dispersion,
and an advanced script that searches the primary and secondary color in a jpeg file. Involves a lot of low-level conversion of RGB arrays to "Hue color space".



Future improvements:
       - A module to allow uploading your own jpeg files, of course there are security and size concerns, such as the size of jpeg file, but since this is
       just a personal project for now, uploading to local folder is good enough, no need for blob type in database
       - Removing the more basic effects, most of the effects are in there, simply for practice, and are imported by other advanced effects function.
       - Some functions return RGB array, and some functions return color identifier/resource, later will have to decide on a more uniform way for functions to behave
