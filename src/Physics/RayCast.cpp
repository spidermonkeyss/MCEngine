#include "RayCast.h"

Ray RayCast::Cast(Vector3 startPoint, Vector3 direction, float length, ChunkHandler* chunkHandler)
{
	//std::cout << "Ray: startPoint:" << startPoint.ToString()<< " direction:" << direction.ToString() << " length:" << length << std::endl;

	Ray ray;
	ray.hit = false;
	ray.block = nullptr;
	ray.blockFace = BlockFace::unresolved;
	ray.rLength = 0;

	direction = direction.Normal();

	//Set up ray bounding box
	Vector3 endPoint = startPoint + (direction * length);
	Vector3 rayBoundStart;
	rayBoundStart.x = std::min(startPoint.x, endPoint.x);
	rayBoundStart.y = std::min(startPoint.y, endPoint.y);
	rayBoundStart.z = std::min(startPoint.z, endPoint.z);
	Vector3 rayBoundEnd;
	rayBoundEnd.x = std::max(startPoint.x, endPoint.x);
	rayBoundEnd.y = std::max(startPoint.y, endPoint.y);
	rayBoundEnd.z = std::max(startPoint.z, endPoint.z);

	//Get all blocks in rays bounding box using world pos
	for (int y = rayBoundStart.y; y <= rayBoundEnd.y; y++)
	{
		for (int z = rayBoundStart.z; z <= rayBoundEnd.z; z++)
		{
			for (int x = rayBoundStart.x; x <= rayBoundEnd.x; x++)
			{
				BlockData* bd = chunkHandler->GetBlockFromWorldPosition(x, y, z);
				//Check that block is not air
				if (bd->blockId != Block::Air)
				{
					Vector3 blockWorldPos(x, y, z);
					if (bd->blockId != 0)
					{
						for (int face = 0; face < 6; face++)
						{
							//Check that the ray isnt paraelle with face
							Vector3 planeNormal = BlockFace::GetNormal((BlockFace::Face)face);
							float rayPlane_dot = Vector3::Dot(direction, planeNormal);
							if (rayPlane_dot == 0.0f)
								std::cout << "is 0";

							if (rayPlane_dot != 0)
							{
								//Get shortest distance from startpoint to plane
								float d = 0;
								switch (face)
								{
								case 0://North
									d = abs(startPoint.z - (blockWorldPos.z - 0.5f));
									break;
								case 1://East
									d = abs(startPoint.x - (blockWorldPos.x + 0.5f));
									break;
								case 2://South
									d = abs(startPoint.z - (blockWorldPos.z + 0.5f));
									break;
								case 3://West
									d = abs(startPoint.x - (blockWorldPos.x - 0.5f));
									break;
								case 4://bot
									d = abs(startPoint.y - (blockWorldPos.y - 0.5f));
									break;
								case 5://top
									d = abs(startPoint.y - (blockWorldPos.y + 0.5f));
									break;
								default:
									break;
								}

								//Get ray length
								float t = 1.0f - abs(Vector3::Dot(direction, planeNormal)) + d;

								//Get intersect point with plane
								Vector3 p = startPoint + (direction * t);

								//Check that point is on face
								Vector3 blockPointDifference = blockWorldPos - p;
								if (abs(blockPointDifference.x) <= 0.5f && abs(blockPointDifference.y) <= 0.5f && abs(blockPointDifference.z) <= 0.5f)
								{
									//if this is the first hit
									if (ray.hit == false)
									{
										ray.hit = true;
										ray.rLength = t;
										ray.rDir = direction;
										ray.rPos = startPoint;
										ray.blockFace = (BlockFace::Face)face;
										ray.block = bd;
									}
									//Check if face intersect point is shortest length
									else if (t < ray.rLength)
									{
										ray.rLength = t;
										ray.rDir = direction;
										ray.rPos = startPoint;
										ray.blockFace = (BlockFace::Face)face;
										ray.block = bd;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	return ray;
}
