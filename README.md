# OpenGL_AirplaneSim


////////////////// SETUP ///////////////////
Once you have cloned the code files, do the following steps to ensure that the project works. 
1. Right click the "Solution 'OpenGL'" project in the solution explorer. Match the UI with the screenshot in the project called "SolutionSettings.png". 
2. Right click the project OpenGL in visual studio solution explorer and select properties. Go under Configuration Properties -> Debugging -> Environment and add the following line:
PATH=%PATH%;$(SolutionDir)OpenGL\lib;
3. In the properties window go under Configuration Properties -> C/C++/ -> General -> Additional Include Directories and add the following line:
$(SolutionDir)OpenGL\include;%(AdditionalIncludeDirectories)
4. In the properties window go under Configuration Properties -> Linker -> General -> Additional Library Directories and add the following line:
$(SolutionDir)OpenGL\lib;%(AdditionalLibraryDirectories)
5. In the properties window go under Configuration Properties -> Linker -> Input -> Additional Dependencies and add the following line:
glew32.lib; glew32s.lib; SDL2.lib; SDL2main.lib; SDL2test.lib; OpenGL32.lib;


///////////////// Controls //////////////////
This simulator is a work in progress for Aersp 424. Some of the code is based on two opengl tutorials by Bennybox and TheCherno found on Youtube. 
When running the simulator on a local machine using visual studio, a menu will show. Select the "Test Texture and Object" tab in the test menu.
Then select the "Camera Position Behind" radio button. 
Next, hold space bar until z camera position on the user interface reads -1. 
Hold the down arrow until the camera y position reads -10.

The controls for this program are the following. The position of the camera can be controlled using z, space bar, left arrow, right arrow, up arrow, down arror. 
The controls for the airplane are "asdw". 
To control the position of the camera you can use the up, down, left, right arrow key. You will notice that the terrain ends after a certain time. 
The terrain needs to be regenerated to make the simulator look like the airplane travels seamlessly through the air. 
