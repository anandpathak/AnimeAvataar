# AnimeAvataar
[![Travis](https://img.shields.io/travis/rust-lang/rust.svg)]()
[![CocoaPods](https://img.shields.io/cocoapods/l/AFNetworking.svg)]()
[![Libraries.io for releases](https://img.shields.io/librariesio/release/hex/phoenix/1.0.3.svg)]()
This application is build using dlib library in C++. 
###### You : "Hey, what are you trying to do ? "  
Me : "I wanted to create an anime face from a normal face. like  this one"
  ![alt tag](http://www.jailbreakmodo.com/wp-content/uploads/make-face-cartoon.jpg)
  
  reference: http://www.jailbreakmodo.com/
###### You :"How are you gonna do this ? "
  Me : "Currently there is two way to achieve, one is by extracting the feature of the face like ``Face Shape``: ['round','square','oval' ,'etc',] ``Nose shape``: ['wide','long','small and wide'] " other feautes like colour, eye shape, forehead etc and with these features create an image. another way is to extract face shape from the landmark detected and then transform the shape to an anime image. " 
###### You "cool, what library are you using"
  Me : "currently using [dlib](http://dlib.net) for facial landmark detection "
###### You "Can I contribute to your project ?"
  Me : "of course ! just hit the fork and start !"
###### You "Can you tell me how to setup this project"
  Me : "okay "
##Setup 
 - `git clone $project`
 - `download dlib and setup in  the project`
 - ` cmake ${project directory } `
 -  ` make `
 -  this will build an executable file in exec folder ! 
