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

	std::list<Edge*> edges_source_ptrs;
	std::list<Edge*> edges_target_ptrs;

	std::list<Hyperedge*> hyperedges_ptrs;

	void remove_hyperedge(int id);

};

// a unidirectional non-hyper edge
struct Edge
{
	Node* source_node_ptr;
	Node* target_node_ptr;

};

// hyperedge
struct Hyperedge
{
	int type;
	NTLabel label;
	std::vector<Node*> attachment_nodes_ptrs;

	int id;

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

	Hyperedge* get_next_hyperedge_to_transform();

	void remove_hyperedge(int id);

};

// a graph which is intended to replace a hyperedge
struct subGraph
{

	std::vector<Node> nodes;
	std::vector<Edge> edges;
	std::vector<Hyperedge> hyperedges;


	int type;
	std::vector<Node*> external_nodes;

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

