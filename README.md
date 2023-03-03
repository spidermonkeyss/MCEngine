# MCEngine
Minecraft style engine using OpenGL

<h2>BUGS</h2>
<ul>
    <li>If entity moves more than 0.5 units on a frame they will clip through blocks. I may implement sweep collisions later but right now i just don't like the entites move more than 0.45 units per frame</li>
    <li>Raycast doesn't always hit the correct face when coordindates are negative</li>
    <li>Chunk borders don't update when removing blocks on the border</li>
    <li>Edge cathcing on collisions of removed blocks</li>
</ul>