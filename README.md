# MCEngine
Minecraft style engine using OpenGL

<p>Need a folder called Libraries two folders up from from soluition and project files.</p>
<p>The folder has the files from my Project-Libraries repository.</p>
<p>To build the project run the "RunPremake.bat" file</p>
<p>The bat file runs this "call premake5.exe vs2019 PAUSE". This works for vs 2022 but you need to retarget the solution after opening it in vs. In the tab Project->Retarget solution</p>

<h2>BUGS</h2>
<ul>
    <li>If entity moves more than 0.5 units on a frame they will clip through blocks. I may implement sweep collisions later but right now i just don't like the entites move more than 0.45 units per frame</li>
    <li>Raycast doesn't always hit the correct face when coordindates are negative</li>
    <li>Chunk borders don't update when removing blocks on the border</li>
    <li>Edge cathcing on collisions of removed blocks</li>
</ul>