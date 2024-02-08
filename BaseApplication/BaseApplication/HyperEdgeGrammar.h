#pragma once

#include <vector>
#include <list>
#include <map>



enum class NTLabel {S};

struct Edge;
struct Hyperedge;

// a single node
struct Node
{
	int sub_node_ID;
	int node_ID;

	std::list<int> edges_source;
	std::list<int> edges_target;

	std::list<int> hyperedges;

	void remove_hyperedge(int id);

	//

	std::list<Edge*> edges_source_ptrs;
	std::list<Edge*> edges_target_ptrs;

	std::list<Hyperedge*> hyperedges_ptrs;


};

// a unidirectional non-hyper edge
struct Edge
{
	int sub_edge_ID;
	int edge_ID;

	int source_node_ID;
	int target_node_ID;

	int source_node_sub_ID;
	int target_node_sub_ID;

	//

	Node* source_node_ptr;
	Node* target_node_ptr;

};

// hyperedge
struct Hyperedge
{
	int sub_hyperedge_ID;
	int hyperedge_ID;

	int type;
	std::vector<int> sub_attachment_nodes;
	std::vector<int> attachment_nodes;

	NTLabel label;

	//

	std::vector<Node*> attachment_nodes_ptrs;

};

struct GraphMapping
{
	std::map<Node*, Node*> node_map;
	std::map<Edge*, Edge*> edge_map;
	std::map<Hyperedge*, Hyperedge*> hyperedge_map;
};


// hypergraph representing the graph which is being transformed
struct Graph
{

	std::vector<Node> nodes;
	std::vector<Edge> edges;

	std::list<Hyperedge> hyperedges;
	int next_hyperedge_id;

	int get_next_hyperedge_to_transform();
	Hyperedge* get_hyperedge_from_id(int id);

	Node* get_node_from_id(int id);

	void remove_hyperedge(int id);

};

// a graph which is intended to replace a hyperedge
struct subGraph
{

	std::vector<Node> nodes;
	std::vector<Edge> edges;
	std::vector<Hyperedge> hyperedges;


	int type;
	std::vector<int> external_nodes;

	Node* get_external_node(int index);
	Node* get_node_from_sub_id(int sub_id);

};

// a production representing a transformation from hyperedge labelled lhs to subgraph rhs
struct Production
{
	NTLabel lhs;
	subGraph rhs;
	int weight;
};


// a set of productions which have a common lhs label
struct ProductionSet
{
	NTLabel lhs_label;
	int num_productions;
	int weight_total;
	std::vector<Production> productions;

	Production* select_rule_to_apply();

};

// a collection of rules and methods for applying those rules to a given graph
class HyperEdgeGrammar
{

	std::vector<ProductionSet> rules;


	Graph graph;

	HyperEdgeGrammar();
	~HyperEdgeGrammar();


	void GenerateLevel();


	void single_transformation();




};

