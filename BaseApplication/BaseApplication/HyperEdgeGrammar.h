#pragma once

#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>

#include <glm/glm.hpp>

// hyperedge labels determine which rules are used to transform a hyperedge
enum class HyperedgeLabel { MOVE, IN_AIR, KICKING, DIVING };

// edge labels represent a move the player can perform
enum class EdgeLabel { jump, long_jump, backflip, dive, dive_spring, kick, deflect,};

// unused label showing if action point is in mid air or not
enum class NodeLabel { platform, intermediate };

class Edge;
class Hyperedge;
class Graph;

struct GLFWwindow;

// a single node
class Node
{
private:
	// unique identifier for the current node
	std::string name;

	// sets of all edges (referenced by name) connected to the current node
	std::set<std::string> edges_source;
	std::set<std::string> edges_target;

	// set of all hyperedges (referenced by name) attached to the current node
	std::set<std::string> hyperedges;

public:

	Node();
	~Node();

	void set_name(std::string new_name) { name = new_name; };

	std::string get_name() { return name; };
	std::set<std::string>& get_sources() { return edges_source; };

	void add_source_edge(const std::string& name);
	void add_target_edge(const std::string& name);
	void add_hyperedge(const std::string& name);
	void remove_hyperedge(const std::string& name);

	// adds prefix to names of node and references to connected elements (when inserting into graph)
	void update_names(const std::string& prefix);

	// copy connected elements to other node (when glueing external and attachment nodes)
	void copy_elements_to_node(Node* n);

	// updates references to this node's name in each connected element (when glueing external and attachment nodes)
	void update_name_in_connected_elements(Graph* level_graph, std::string new_name);

};

// a unidirectional, labelled, not-hyper edge
class Edge
{
private:
	// unique identifier
	std::string name;

	// type of move
	EdgeLabel label = EdgeLabel::jump;

	// name of source and target nodes
	std::string source_node;
	std::string target_node;

public:

	Edge() {};
	Edge(EdgeLabel l, std::string nm, std::string src, std::string tar)
	{
		label = l;
		name = nm;
		source_node = src;
		target_node = tar;
	};

	void set_source(std::string n) { source_node = n; };
	void set_target(std::string n) { target_node = n; };

	void set_name(std::string new_name) { name = new_name; };
	void set_label(EdgeLabel e_label) { label = e_label; };

	std::string get_name() { return name; };
	std::string get_target() { return target_node; };
	std::string get_source() { return source_node; };
	EdgeLabel get_label() { return label; };


	// adds prefix to all names (when inserting into graph)
	void update_names(std::string prefix);

	// update name of source node (when glueing external and attachment nodes)
	void update_source_name(std::string name);

	// update name of target node (when glueing external and attachment nodes)
	void update_target_name(std::string name);

	// get string name of move
	static std::string text_from_label(EdgeLabel in_label);

};

// hyperedge
class Hyperedge
{
private:
	// unique string identifier
	std::string name;

	HyperedgeLabel label = HyperedgeLabel::MOVE;

	// names of all attached nodes
	std::vector<std::string> attachment_nodes;


public:

	Hyperedge() {};
	Hyperedge(std::string nm, HyperedgeLabel l)
	{
		name = nm;
		label = l;
	}

	void set_name(std::string new_name) { name = new_name; };
	void set_label(HyperedgeLabel h_label) { label = h_label; };
	void add_attachment_node(std::string n_name) { attachment_nodes.push_back(n_name); };
	
	std::string get_name() { return name; };
	HyperedgeLabel get_label() { return label; };
	std::vector<std::string>& get_attachment_nodes() { return attachment_nodes; };

	std::string get_attachment_node(int index);

	// remove references to this hyperedge from attached nodes (when replacing from graph)
	void delete_from_attachment_nodes(Graph* graph);
	
	// add prefix to all names (when inserting into graph)
	void update_names(std::string prefix);

	// update name of particular attachment node (when glueing external and attachment nodes)
	void update_node_name(std::string old_name, std::string new_name);
	
	// get string name of label
	static std::string text_from_label(HyperedgeLabel in_label);


};


// graph (or hypergraph) can be a replacement graph or main graph
class Graph
{
private:

	// all elements stored by name
	std::map<std::string, Node> nodes;
	std::map<std::string, Edge> edges;
	std::map<std::string, Hyperedge> hyperedges;

	// nodes in the graph which should be glued in a replacement (if used as a replacement graph)
	std::vector<std::string> external_nodes;

	bool is_external_node(std::string name);

public:

	// remove all elements in graph
	void clear_graph();

	// are there any hyperedges in the graph
	bool do_hyperedges_remain();

	// return a hyperedge which should be the target for the next replacement
	Hyperedge* select_hyperedge_to_replace();

	void add_edge(Edge& e);
	void add_hyperedge(Hyperedge& h);
	void add_node(Node& n);

	void add_nodes(int num, Node* in_nodes);
	void add_edges(int num, Edge* in_edges);

	void add_external_node(std::string nm)
	{
		external_nodes.push_back(nm);
	};

	Node* get_node_from_name(std::string name);
	Edge* get_edge_from_name(std::string name);
	Hyperedge* get_hyperedge_from_name(std::string name);

	Node* get_external_node(int index);

	// copy all elements except external nodes to another graph (when inserting as a replacement graph)
	void copy_elements_to_level_graph(Graph* level_graph, std::string prefix);

	// glue external nodes onto another graph (when inserting into another graph)
	void glue_nodes(Graph* level_graph, Hyperedge* hyperedge);

	void remove_hyperedge(std::string name);

	// output this graph to dot format + copy to clipboard (for web visualisation)
	void output_dot(GLFWwindow* window);

	std::map<std::string, Node>& get_nodes() { return nodes; };
	std::map<std::string, Edge>& get_edges() { return edges; };
	std::map<std::string, Hyperedge>& get_hyperedges() { return hyperedges; };
};


// a production representing a transformation from hyperedge labelled lhs to subgraph rhs
struct Production
{
	Production(HyperedgeLabel l, int w)
	{
		target_label = l;
		weight = w;
	}
	
	// kind of hyperedge this rule can replace
	HyperedgeLabel target_label;

	// graph to replace hyperedge with
	Graph replacement_graph;

	// relative probability of selection
	int weight;
};


// a set of productions which have a common lhs label
struct ProductionSet
{
	// kind of hyperedge all rules in this set target
	HyperedgeLabel lhs_label;
	int num_productions;
	int weight_total;

	// collection of hyperedge replacement rules
	std::vector<Production> productions;

	// select a random rule in this set to be performed
	Production* select_rule_to_apply();

	void AddRule(Production p) { productions.push_back(p); };
	void update_weight();

};


// Contains all elements and functions required to perform full hyperedge replacement graph transformations
class HyperEdgeGrammar
{

	std::vector<ProductionSet> rules;

	int replacement_count = 0;

	Graph level_graph;

public:

	HyperEdgeGrammar();
	~HyperEdgeGrammar();

	// build initial level graph state
	void make_starting_graph();

	// build rule sets
	void make_rules();

	// reset graph to starting graph
	void reset_graph();

	// perform a single step of graph transformation
	void generate_graph(GLFWwindow* window);

	// do a single hyperedge replacement
	void single_replacement(GLFWwindow* window, std::string prefix);

	// generate a complete graph
	void GenerateWholeGraph(GLFWwindow* window);
	
	// 
	void get_data(int& diff, int& vari);
	void get_dist(int& num, int& jumps, int& ljumps, int& bflips, int& dives, int& dsprings, int& kicks, int& deflects);

	Graph get_output_graph();

	// copy dot format of current graph to clipboard
	void copy_current_graph(GLFWwindow* window);


};

