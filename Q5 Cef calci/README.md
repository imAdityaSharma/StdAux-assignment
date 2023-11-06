<h2> The whole package of Chromium Embedded Framework cannot be added here due to size restrictions. So only build files and Executables are compressed in .7z format here. </h2>

The whole package can be downloaded from <a href="https://drive.google.com/file/d/1f_e75Wzdlu244b5y4qP-ikSZLrHn3Rhv/view?usp=drive_link" > This </a> link.

<h2>Execution Instrution for package downloaded from github repo</h2>
<list>
  <item>1. Download compressed files</item><br>
  <item>2. Extract Using 7zip </item><br>
  <item>3. Navigate to /Debug and execute cefsimple.exe </item>  
</list>


<h2>Execution Instruction for package downloaded from provided Link</h2>
<list>
  <item>1 )   Download compressed files From the link. </item><br><br>
  <item>2 )    Extract Using 7zip. (compressed size is 1GB, after extraction, it can be around 8 GB) </item><br><br>
  <item>3 )     Open Visual Studio 17 2022 in the current working directory.</item>  <br>
  <item> 3.1)   Please make sure all the latest Cmake, Python, and Windows SDK 10.x.x are installed properly and added to path or configured properly.</item><br>
  <item>3.2)    Open terminal in root of the project and execute the following commands.</item><br>
  <item>3.3)   <b> 'cd build' </b></item><br>
  <item>3.4)   <b> 'rm -r * '</b> </item><br>
  <item>3.5)     After successful execution of the above commands execute 'cmake -G " Visual Studio 17" -A x64 ..'</item><br><br>
  <item>4 )     Navigate to 'cef-project\build' and open visual studio</item><br>
  <item>4.1)    Inside visual studio find .sln file in explorer and click it to open solution explorer</item> <br>
  <item>4.2)   right click on cefsimple and set it as startup project </item><br>
  <item>4.3)   Now navigate into cefsimple and find simple_app.cc and open it </item><br>
  <item>4.4)   go to line 108 Or search for code "if (url.empty())" </item><br>
  <item>4.5)   Here we can set the default URL to be loaded upon application execution after the build </item>
  <item>4.6)   Set url as <I> https://imadityasharma.github.io/ </i>.<br>            This is where I have hosted webpages for the application. </item><br>
  <item>4.7)    Now Run "local windows Debugger" or go to Build->Build Solution ( Cltr+Shift+B ) </item><br>
  <item>4.8)    After debugging or solution building it will launch cefsimple.exe window with configured default url.</item><br>
</list>
