#pragma once

#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>

#include <glm/glm.hpp>

enum class HyperedgeLabel { MOVE, IN_AIR, KICKING, DIVING };
enum class EdgeLabel { jump, long_jump, backflip, dive, dive_spring, kick, deflect,};
enum class NodeLabel { platform, intermediate };

class Edge;
class Hyperedge;
class Graph;

struct GLFWwindow;

// a single node
class Node
{
private:
	std::string name;

	std::set<std::string> edges_source;
	std::set<std::string> edges_target;

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

	void update_names(const std::string& prefix);
	void update_name_in_connected_elements(Graph* level_graph, std::string new_name);

	void copy_elements_to_node(Node* n);

};

// a unidirectional non-hyper edge
class Edge
{
private:
	EdgeLabel label = EdgeLabel::jump;
	std::string source_node;

	std::string name;
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


	void update_names(std::string prefix);
	void update_source_name(std::string name);
	void update_target_name(std::string name);

	static std::string text_from_label(EdgeLabel in_label);

};

// hyperedge
class Hyperedge
{
private:
	//int type;

	std::string name;
	HyperedgeLabel label = HyperedgeLabel::MOVE;
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
	void delete_from_attachment_nodes(Graph* graph);
	
	void update_names(std::string prefix);
	void update_node_name(std::string old_name, std::string new_name);

	static std::string text_from_label(HyperedgeLabel in_label);





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

	void clear_graph();

	bool do_hyperedges_remain();

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
	void copy_elements_to_level_graph(Graph* level_graph, std::string prefix);
	void glue_nodes(Graph* level_graph, Hyperedge* hyperedge);

	void remove_hyperedge(std::string name);


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

	Production* select_rule_to_apply();

	void AddRule(Production p) { productions.push_back(p); };
	void update_weight();

};


// a collection of rules and methods for applying those rules to a given graph
class HyperEdgeGrammar
{

	std::vector<ProductionSet> rules;

	int replacement_count = 0;

	Graph level_graph;

public:

	HyperEdgeGrammar();
	~HyperEdgeGrammar();

	void make_starting_graph();
	void make_rules();

	void reset_graph();

	void generate_graph(GLFWwindow* window);
	void single_replacement(GLFWwindow* window, std::string prefix);
	void GenerateWholeGraph(GLFWwindow* window);
	

	Graph get_output_graph();

	void copy_current_graph(GLFWwindow* window);


};

