#pragma once

#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>

#include <glm/glm.hpp>

enum class HyperedgeLabel { S };
enum class EdgeLabel { a };

class Edge;
class Hyperedge;
class Graph;

// a single node
class Node
{
private:
	std::set<std::string> edges_source;
	std::set<std::string> edges_target;

	std::set<std::string> hyperedges;


public:
	std::string name;

	void add_source_edge(const std::string& name);
	void add_target_edge(const std::string& name);
	void add_hyperedge(const std::string& name);
	void remove_hyperedge(const std::string& name);

	void update_names(const std::string& prefix);
	void update_name_in_connected_elements(Graph* level_graph, std::string new_name);

	void copy_elements_to_node(Node* n);

};

// a unidirectional non-hyper edge
class Edge
{
private:
	EdgeLabel label;
	std::string source_node;
	std::string target_node;

	//void replace_target(Node* n);
	//void replace_source(Node* n);

public:
	std::string name;

	void update_names(std::string prefix);
	void update_source_name(std::string name);
	void update_target_name(std::string name);

};

// hyperedge
class Hyperedge
{
private:
	int type;

	std::vector<std::string> attachment_nodes;

public:
	std::string name;
	HyperedgeLabel label;


	std::string get_attachment_node(int index);
	void delete_from_attachment_nodes(Graph* graph);
	
	void update_names(std::string prefix);
	void update_node_name(std::string old_name, std::string new_name);

};


// graph!
class Graph
{
private:

	std::map<std::string, Node> nodes;
	std::map<std::string, Edge> edges;
	std::map<std::string, Hyperedge> hyperedges;

	std::vector<std::string> external_nodes;

	bool is_external_node(std::string name);

public:
	bool do_hyperedges_remain();

	Hyperedge* select_hyperedge_to_replace();

	void add_edge(Edge& e);
	void add_hyperedge(Hyperedge& h);
	void add_node(Node& n);

	Node* get_node_from_name(std::string name);
	Edge* get_edge_from_name(std::string name);
	Hyperedge* get_hyperedge_from_name(std::string name);

	Node* get_external_node(int index);
	void copy_elements_to_level_graph(Graph* level_graph, std::string prefix);
	void glue_nodes(Graph* level_graph, Hyperedge* hyperedge);

	void remove_hyperedge(std::string name);

};


// a production representing a transformation from hyperedge labelled lhs to subgraph rhs
struct Production
{
	HyperedgeLabel target_label;
	Graph replacement_graph;
	int weight;
};


// a set of productions which have a common lhs label
struct ProductionSet
{
	HyperedgeLabel lhs_label;
	int num_productions;
	int weight_total;
	std::vector<Production> productions;

	Graph* select_rule_to_apply();

};


// a collection of rules and methods for applying those rules to a given graph
class HyperEdgeGrammar
{

	std::vector<ProductionSet> rules;

	int replacement_count = 0;

	Graph level_graph;

	HyperEdgeGrammar();
	~HyperEdgeGrammar();


	void generate_graph();
	void single_replacement(std::string prefix);

	Graph get_output_graph();



	void output_dot();

};

