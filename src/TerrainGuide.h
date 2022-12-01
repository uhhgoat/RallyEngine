/*! \page terraindemo Creating Terrain

\section tersetup Terrain Setup
Terrains are a unique object type of which there is at most one per scene. They have their own generation and collision processing. \n
Any object can be made to collide with the terrain, location data is not returned by the terrain on a collision. All terrains must be square. \n
To start using terrains, one or more terrain must be pre-loaded in the LoadResources file. \n
You must pass in a name, a square heightmap file, the desired side length, the maximum height, a height offset, the desired texture, \n
and the number of times you would like the texture to repeat in the x and y directions.
\n
\code
TerrainObjectManager::Load("terrain", "hills.tga", 10000, 750, -10, "grass", 100, 100);
\endcode
\n
\section tershow Adding Terrain to Scene
To make a scene show up in a scene, you must set the terrain in initialize. \n
In addition, any objects that you would like to collide with the terrain must be set to collide with the terrain. \n
\code
Initialize()
{
	SetTerrain("terrain");
	SetCollisionTerrain<Bullet>();
}
\endcode
\section tertools Terrain Tools
In addition to having collision, the terrain provides height and normal data based on Vector position input. \n
If you would like an object to be on top of the terrain at any given point, or be aligned with the angle of the terrain, \n
this can be achieved with two helper methods. The terrain can be accessed through the scene.\n
In addition, you may use the help of the math tools provided by RallyMathTools to help with some calculation. \n
In particular, you may pass in the normal value to GetRotationTo(Vect _a) to return the rotation matrix to align with the normal. \n
\n
\code
float h = SceneManager::GetCurrentScene()->GetTerrain()->GetHeight(Vect(x, y, z));
Vect normal = SceneManager::GetCurrentScene()->GetTerrain()->GetNormal(Vect(x, y, z));
Matrix R = RallyMathTools::GetRotationTo(normal);
\endcode
\n
That is all that is needed to build and use a terrain. Pre-loaded are cleaned up on their own \n
at the end of the program like other loaded assets. \n
\n
\n
\n
*/