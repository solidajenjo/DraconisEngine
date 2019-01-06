#include "QuadTree.h"

QTNode::QTNode()
{
	aabb = new AABB();
}

QTNode::~QTNode()
{
	RELEASE(aabb);
	for (QTNode* node : lowerNodes)
	{
		RELEASE(node);
	}
}

std::vector<QTNode*>& QTNode::Flush()
{
	float3 center = aabb->CenterPoint();
	float3 newSize = aabb->Size();
	newSize.x *= .5f;
	newSize.z *= .5f;

	float3 newCenter;
	newCenter.y = center.y;

	QTNode* n1 = new QTNode();
	n1->depth = depth + 1;
	newCenter.x = center.x - newSize.x * 0.5f;
	newCenter.z = center.z - newSize.z * 0.5f;
	n1->aabb->SetFromCenterAndSize(newCenter, newSize);
	lowerNodes.push_back(n1);

	QTNode* n2 = new QTNode();
	n2->depth = depth + 1;
	newCenter.x = center.x - newSize.x * 0.5f;
	newCenter.z = center.z + newSize.z * 0.5f;
	n2->aabb->SetFromCenterAndSize(newCenter, newSize);
	lowerNodes.push_back(n2);

	QTNode* n3 = new QTNode();
	n3->depth = depth + 1;
	newCenter.x = center.x + newSize.x * 0.5f;
	newCenter.z = center.z - newSize.z * 0.5f;
	n3->aabb->SetFromCenterAndSize(newCenter, newSize);
	lowerNodes.push_back(n3);

	QTNode* n4 = new QTNode();
	n4->depth = depth + 1;
	newCenter.x = center.x + newSize.x * 0.5f;
	newCenter.z = center.z + newSize.z * 0.5f;
	n4->aabb->SetFromCenterAndSize(newCenter, newSize);
	lowerNodes.push_back(n4);

	for each(GameObject* go in bucket)
	{
		for each(QTNode* node in lowerNodes)
		{
			if (go->aaBBGlobal->Intersects(*node->aabb) || node->aabb->Contains(*go->aaBBGlobal))
			{
				node->bucket.push_back(go);
			}
		}
	}	
	bucket.resize(0);
	return lowerNodes;
}

