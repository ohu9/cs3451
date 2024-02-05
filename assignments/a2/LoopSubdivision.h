#ifndef __LoopSubdivision_h__
#define __LoopSubdivision_h__
#include <unordered_map>
#include <vector>
#include "Mesh.h"

/* HELPER FUNCTIONS */
int find_opposite_vertex(Vector3i tri, int v1, int v2) { // properly debugged
	for(int j = 0; j < 3; j++){
		if(tri[j] != v1 && tri[j] != v2) {
			return tri[j];
		}
	}
	return -1;
}

Vector2i sorted(int a, int b) {
	return (a < b) ? Vector2i(a, b) : Vector2i (b, a);
}

/* SUBDIVISON ALGORITHM */
inline void LoopSubdivision(TriangleMesh<3>& mesh)
{
	std::vector<Vector3>& old_vtx=mesh.Vertices();
	std::vector<Vector3i>& old_tri=mesh.Elements();
	std::vector<Vector3> new_vtx;		////vertex array for the new mesh
	std::vector<Vector3i> new_tri;		////element array for the new mesh

	
	new_vtx=old_vtx;	////copy all the old vertices to the new_vtx array

	////step 0: update auxiliary data structures (edge_tri_map, vtx_vtx_map)
	std::unordered_map<Vector2i,int> edge_odd_vtx_map;				//key: edge, value: new (odd) vertex that is added in step 1; useful for step 2
	std::unordered_map<Vector2i,std::vector<int>> edge_tri_map;		//key: edge, value: vector containing adjacent triangles
	std::unordered_map<int,std::vector<int>> vtx_vtx_map;			//key: vertex, value: vector containing adjacent vertices

	for( int i = 0; i < old_tri.size(); i++ ){ //iterate through each triangle
		const Vector3i& tri = old_tri[i];
		for(int j = 0; j < 3; j++){ //iterate through each vertex
			int vtx = tri[j];
			int adjv1 = tri[(j + 1) % 3];
			int adjv2 = tri[(j + 2) % 3];
			//build vtx_vtx_map
			if(std::find(vtx_vtx_map[vtx].begin(), vtx_vtx_map[vtx].end(), adjv1) == vtx_vtx_map[vtx].end()) {vtx_vtx_map[tri[j]].push_back(adjv1);}
			if(std::find(vtx_vtx_map[vtx].begin(), vtx_vtx_map[vtx].end(), adjv2) == vtx_vtx_map[vtx].end()) {vtx_vtx_map[tri[j]].push_back(adjv2);}

			// build edge_tri_map
			Vector2i edge(sorted(vtx, adjv1));
			edge_tri_map[edge].push_back(i);

	////step 1: add odd vertices
			if(auto containsEdge = edge_odd_vtx_map.find(edge); containsEdge == edge_odd_vtx_map.end()) {
				Vector3 midpt = 0.5 * (old_vtx[edge[0]] + old_vtx[edge[1]]);
				new_vtx.push_back(midpt);
				edge_odd_vtx_map[edge] = new_vtx.size() - 1;
			}
		}

		////add four new triangles to new_tri
		int m0 = edge_odd_vtx_map[sorted(tri[0], tri[1])];
		int m1 = edge_odd_vtx_map[sorted(tri[1], tri[2])];
		int m2 = edge_odd_vtx_map[sorted(tri[2], tri[0])];
		new_tri.push_back(Vector3i{tri[0], m0, m2});
		new_tri.push_back(Vector3i{tri[1], m0, m1});
		new_tri.push_back(Vector3i{tri[2], m1, m2});
		new_tri.push_back(Vector3i{m0, m1, m2});
	}

	//step 2: update odd vertex positions
	for (const auto & [edge, triangles] : edge_tri_map) {
		int odd_vtx = edge_odd_vtx_map[edge];
		Vector3i t0 = old_tri[triangles[0]];
		Vector3i t1 = old_tri[triangles[1]];
		Vector3 opp_v0 = new_vtx[find_opposite_vertex(t0, edge[0], edge[1])];
		Vector3 opp_v1 = new_vtx[find_opposite_vertex(t1, edge[0], edge[1])];

		new_vtx[odd_vtx] = .125*(opp_v0 + opp_v1) + 0.375*(new_vtx[edge[0]] + new_vtx[edge[1]]);
	}
	
	// ////step 3: update even vertex positions
	for (auto & [vtx, neighbors] : vtx_vtx_map) {
		float n = (float)vtx_vtx_map[vtx].size();
		float beta = 3./(8.*n);
		Vector3 neighbor_sum(0, 0, 0);
		for (int i = 0; i < n; i++) {
			neighbor_sum += old_vtx[neighbors[i]];
		}
		new_vtx[vtx] = (old_vtx[vtx]*(1. - (n * beta))) + beta*neighbor_sum;
	}

	////update subdivided vertices and triangles onto the input mesh
	old_vtx=new_vtx;
	old_tri=new_tri;
}

#endif


/* INSTRUCTIONS */
////step 1: add odd vertices
	////for each old triangle, 
	////add three new vertices (in the middle of each edge) to new_vtx 
	////simultaneously: update auxiliary data structure (edge_odd_vtx_map)
	////add four new triangles to new_tri

////step 2: update the position for each new mid-point vertex: 
	////for each mid-point vertex, find its two end-point vertices A and B, 
	////and find the two opposite-side vertices on the two incident triangles C and D,
	////then update the new position as .375*(A+B)+.125*(C+D)

////step 3: update vertices of each old vertex
	////for each old vertex, find its incident old vertices, and update its position according its incident vertices