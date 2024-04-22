#include "HyperEdgeGrammar.h"

#include <iostream>

#include <stack>

#include <GLFW/glfw3.h>


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"



// ------ NODE FUNCTIONS -------------

void Node::remove_hyperedge(const std::string& name)
{
	hyperedges.erase(name);
}

Node::Node()
{
}

Node::~Node()
{
}

void Node::add_source_edge(const std::string& name)
{
	edges_source.insert(name);
}

void Node::add_target_edge(const std::string& name)
{
	edges_target.insert(name);
}

void Node::add_hyperedge(const std::string& name)
{
	hyperedges.insert(name);
}

void Node::update_names(const std::string& prefix)
{
	//add prefix to name
	name = prefix + name;

	std::stack<std::string> stack;

	// add prefix to hyperedge names
	for (std::string h : hyperedges)
	{
		stack.push(prefix + h);
	}

	hyperedges.clear();

	while (!stack.empty())
	{
		hyperedges.insert(stack.top());
		stack.pop();
	}

	//add prefix to edge source names
	for (std::string es : edges_source)
	{
		stack.push(prefix + es);
	}

	edges_source.clear();

	while (!stack.empty())
	{
		edges_source.insert(stack.top());
		stack.pop();
	}

	//add prefix to edge target names
	for (std::string et : edges_target)
	{
		stack.push(prefix + et);
	}

	edges_target.clear();

	while (!stack.empty())
	{
		edges_target.insert(stack.top());
		stack.pop();
	}


}

//copy each edge and hyperedge to given node
void Node::copy_elements_to_node(Node* n)
{
	// copy hyperedges to node
	for (std::string h : hyperedges)
	{
		n->add_hyperedge(h);
	}

	// copy source edges to node
	for (std::string es : edges_source)
	{
		n->add_source_edge(es);
	}

	// copy target edges to node
	for (std::string et : edges_target)
	{
		n->add_target_edge(et);
	}

}


void Node::update_name_in_connected_elements(Graph* level_graph, std::string new_name)
{

	// update each hyperedge reference
	for (std::string h : hyperedges)
	{
		Hyperedge* hptr = level_graph->get_hyperedge_from_name(h);
		hptr->update_node_name(name, new_name);
	}

	// update each source edge reference
	for (std::string es : edges_source)
	{
		Edge* esptr = level_graph->get_edge_from_name(es);
		esptr->update_source_name(new_name);
	}

	// update each target edge reference
	for (std::string et : edges_target)
	{
		Edge* etptr = level_graph->get_edge_from_name(et);
		etptr->update_target_name(new_name);
	}



}


// ------ EDGE FUNCTIONS -------------


void Edge::update_names(std::string prefix)
{
	name = prefix + name;
	source_node = prefix + source_node;
	target_node = prefix + target_node;

}

void Edge::update_source_name(std::string name)
{
	source_node = name;
}

void Edge::update_target_name(std::string name)
{
	target_node = name;
}

std::string Edge::text_from_label(EdgeLabel in_label)
{
	std::string out;
	switch (in_label)
	{

	case EdgeLabel::jump:
		out = "jump";
		break;
	case EdgeLabel::long_jump:
		out = "long_jump";
		break;
	case EdgeLabel::backflip:
		out = "backflip";
		break;
	case EdgeLabel::dive:
		out = "dive";
		break;
	case EdgeLabel::dive_spring:
		out = "dive_spring";
		break;
	case EdgeLabel::kick:
		out = "kick";
		break;
	case EdgeLabel::deflect:
		out = "deflect";
		break;
	}
	return out;

}


// ------ HYPEREDGE FUNCTIONS --------

// get name of attachment node by index
std::string Hyperedge::get_attachment_node(int index)
{
	if (index >= attachment_nodes.size())
	{
		return "";
	}
	return attachment_nodes.data()[index];
}

//remove references to this hyperedge from it's attachment nodes
void Hyperedge::delete_from_attachment_nodes(Graph* graph)
{
	 
	for (int i = 0; i < attachment_nodes.size(); i++)
	{
		std::string node_name = attachment_nodes.data()[i];
		// get node from graph	
		Node* n = graph->get_node_from_name(node_name);

		// remove this hyperedge
		n->remove_hyperedge(name);

	}

}

//add prefix to all element names
void Hyperedge::update_names(std::string prefix)
{

	name = prefix + name;

	for (int i = 0; i < attachment_nodes.size(); i++)
	{
		attachment_nodes.data()[i] = prefix + attachment_nodes.data()[i];
	}

}

//rename all instances of old name in attachment nodes
void Hyperedge::update_node_name(std::string old_name, std::string new_name)
{
	for (int i = 0; i < attachment_nodes.size(); i++)
	{

		if (attachment_nodes.data()[i] == old_name)
		{
			attachment_nodes.data()[i] = new_name;
		}

	}

}

std::string Hyperedge::text_from_label(HyperedgeLabel in_label)
{
	std::string out;
	switch (in_label)
	{
	case HyperedgeLabel::MOVE:
		out = "MOVE";
		break;
	case HyperedgeLabel::IN_AIR:
		out = "IN_AIR";
		break;
	case HyperedgeLabel::KICKING:
		out = "KICKING";
		break;
	case HyperedgeLabel::DIVING:
		out = "DIVING";
		break;			
	}
	return out;


	return std::string();
}


// ------ GRAPH FUNCTIONS ------------

void Graph::clear_graph()
{
	
	nodes.clear();
	edges.clear();
	hyperedges.clear();
	external_nodes.clear();

}

bool Graph::do_hyperedges_remain()
{
	return !hyperedges.empty();
}

Hyperedge* Graph::select_hyperedge_to_replace()
{
	std::string nm = hyperedges.begin()->first;
	return &hyperedges[nm];

}

void Graph::add_edge(Edge& e)
{
	edges[e.get_name()] = e;
}

void Graph::add_hyperedge(Hyperedge& h)
{
	hyperedges[h.get_name()] = h;
}

void Graph::add_node(Node& n)
{
	nodes[n.get_name()] = n;
}

void Graph::add_nodes(int num, Node* in_nodes)
{
	for (int i = 0; i < num; i++)
	{
		add_node(in_nodes[i]);
	}
}

void Graph::add_edges(int num, Edge* in_edges)
{
	for (int i = 0; i < num; i++)
	{
		add_edge(in_edges[i]);
	}
}

Node* Graph::get_node_from_name(std::string name)
{
	return &nodes[name];
}

Edge* Graph::get_edge_from_name(std::string name)
{
	return &edges[name];
}

Hyperedge* Graph::get_hyperedge_from_name(std::string name)
{
	return &hyperedges[name];
}

Node* Graph::get_external_node(int index)
{
	std::string name = external_nodes.data()[index];
	return &nodes[name];
}

bool Graph::is_external_node(std::string name)
{
	for (int i = 0; i < external_nodes.size(); i++)
	{
		if (external_nodes.data()[i] == name)
		{
			return true;
		}
	}
	return false;
}

// copy each element from replacement graph into level graph
//		skip external nodes
void Graph::copy_elements_to_level_graph(Graph* level_graph, std::string prefix)
{

	// update names in each element
	//	and add to level graph

	//	nodes
	for (auto& n : nodes)
	{
		if (is_external_node(n.first)) 
		{ 
			n.second.update_names(prefix);
			continue; 
		}

		n.second.update_names(prefix);
		level_graph->add_node(n.second);
	}

	//	edges
	for (auto& e : edges)
	{
		e.second.update_names(prefix);
		level_graph->add_edge(e.second);
	}

	//	hyperedges
	for (auto& h : hyperedges)
	{
		h.second.update_names(prefix);
		level_graph->add_hyperedge(h.second);
	}

}

// merge each external node in replacement graph to corresponding attachment node in level graph
void Graph::glue_nodes(Graph* level_graph, Hyperedge* hyperedge)
{

	for (int i = 0; i < external_nodes.size(); i++)
	{
		std::string ext_name = external_nodes.data()[i];
		Node* ext_node = get_node_from_name(ext_name);

		// get attachment node
		std::string att_name = hyperedge->get_attachment_node(i);
		Node* att_node = level_graph->get_node_from_name(att_name);

		//copy elements from external to attachment node
		ext_node->copy_elements_to_node(att_node);

		// update node name in connected edges/hyperedges
		ext_node->update_name_in_connected_elements(level_graph, att_name);

	}



}

void Graph::remove_hyperedge(std::string name)
{

	hyperedges.erase(name);

}

void Graph::output_dot(GLFWwindow* window)
{
	std::string out = "";

	//	digraph {
	out += "digraph {\n";

	//generate node bits

	for (auto n : nodes)
	{
		//		for each source edge, get name of target node
		for (std::string es : n.second.get_sources())
		{
			//	node name -> {
			out += n.second.get_name();
			out += " -> ";

			//		node name
			out += get_edge_from_name(es)->get_target();
			out += " [label = " + Edge::text_from_label(get_edge_from_name(es)->get_label()) + "]";

			out += " ";
			out += ";\n";
		}
		//	}
	}
	//generate hyperedge bits

	for (auto h : hyperedges)
	{
		//  hyperedge name [shape = square]
		out += h.second.get_name() + Hyperedge::text_from_label(h.second.get_label()) + " [shape = square];\n";
		//	hyperedge name -> {
		out += h.second.get_name() + Hyperedge::text_from_label(h.second.get_label());
		out += " -> { ";
		for (std::string att : h.second.get_attachment_nodes())
		{
			//	name of each attachment node
			out += att;
			out += " ";
		}		
		//	}
		out += " };\n";
	}
	//	}
	out += "};";

		glfwSetClipboardString(window, out.c_str());


}

// ------ PRODUCTION FUNCTIONS -------

Production* ProductionSet::select_rule_to_apply()
{

	//generate random number between 0 and total weight of rules
	int num = rand() % weight_total;

	//go through rules till cumulative weight exceeds random number

	int weight_count = 0;
	for (int i = 0; i < productions.size(); i++)
	{
		weight_count += productions.data()[i].weight;
		if (weight_count >= num)
		{
			return &productions.data()[i];
		}

	}
	return &productions.data()[0];


}

void ProductionSet::update_weight()
{
	int total = 0;
	for (int i = 0; i < productions.size(); i++)
	{
		total += productions.data()[i].weight;
	}
	weight_total = total;
	num_productions = productions.size();
}


// ------ GRAMMAR FUNCTIONS ----------


HyperEdgeGrammar::HyperEdgeGrammar()
{

	make_starting_graph();
	make_rules();



}

HyperEdgeGrammar::~HyperEdgeGrammar()
{


}

void HyperEdgeGrammar::make_starting_graph()
{

	Node ns;
	ns.set_name("start");
	
	Node ne;
	ne.set_name("end");

	Hyperedge h;
	h.set_name("h1");
	h.set_label(HyperedgeLabel::MOVE);

	h.add_attachment_node(ns.get_name());
	h.add_attachment_node(ne.get_name());

	ns.add_hyperedge(h.get_name());
	ne.add_hyperedge(h.get_name());


	level_graph.add_node(ns);
	level_graph.add_node(ne);
	level_graph.add_hyperedge(h);



}

void HyperEdgeGrammar::make_rules()
{


	// MOVE Rules
	ProductionSet MoveRules;
	MoveRules.lhs_label = HyperedgeLabel::MOVE;
	{
		Production move_1(HyperedgeLabel::MOVE, 1);

		Node ns[2];
		ns[0].set_name("n0");
		ns[1].set_name("n1");

		Edge e(EdgeLabel::jump, "e0", "n0", "n1");

		ns[0].add_source_edge("e0");
		ns[1].add_target_edge("e0");

		move_1.replacement_graph.add_nodes(2, ns);
		move_1.replacement_graph.add_edge(e);

		move_1.replacement_graph.add_external_node("n0");
		move_1.replacement_graph.add_external_node("n1");

		MoveRules.AddRule(move_1);

	}
	{

		Production move_2(HyperedgeLabel::MOVE, 2);
		
		Node ns[3];
		ns[0].set_name("n0");
		ns[1].set_name("n1");
		ns[2].set_name("n2");

		Edge e(EdgeLabel::jump, "e0", "n0", "n1");

		Hyperedge h("h0", HyperedgeLabel::IN_AIR);
		h.add_attachment_node("n1"); 
		h.add_attachment_node("n2");

		ns[0].add_source_edge("e0");
		ns[1].add_target_edge("e0");

		ns[1].add_hyperedge("h0");
		ns[2].add_hyperedge("h0");

		move_2.replacement_graph.add_nodes(3, ns);
		move_2.replacement_graph.add_edge(e);
		move_2.replacement_graph.add_hyperedge(h);

		move_2.replacement_graph.add_external_node("n0");
		move_2.replacement_graph.add_external_node("n2");

		MoveRules.AddRule(move_2);


	}
	{
		Production move_3(HyperedgeLabel::MOVE, 1);

		Node ns[2];
		ns[0].set_name("n0");
		ns[1].set_name("n1");

		Edge e(EdgeLabel::long_jump, "e0", "n0", "n1");

		ns[0].add_source_edge("e0");
		ns[1].add_target_edge("e0");

		move_3.replacement_graph.add_nodes(2, ns);
		move_3.replacement_graph.add_edge(e);

		move_3.replacement_graph.add_external_node("n0");
		move_3.replacement_graph.add_external_node("n1");

		MoveRules.AddRule(move_3);

	}
	{
		Production move_4(HyperedgeLabel::MOVE, 2);


		Node ns[3];
		ns[0].set_name("n0");
		ns[1].set_name("n1");
		ns[2].set_name("n2");

		Edge e(EdgeLabel::long_jump, "e0", "n0", "n1");

		Hyperedge h("h0", HyperedgeLabel::IN_AIR);
		h.add_attachment_node("n1");
		h.add_attachment_node("n2");

		ns[0].add_source_edge("e0");
		ns[1].add_target_edge("e0");

		ns[1].add_hyperedge("h0");
		ns[2].add_hyperedge("h0");

		move_4.replacement_graph.add_nodes(3, ns);
		move_4.replacement_graph.add_edge(e);
		move_4.replacement_graph.add_hyperedge(h);

		move_4.replacement_graph.add_external_node("n0");
		move_4.replacement_graph.add_external_node("n2");

		MoveRules.AddRule(move_4);
	}
	MoveRules.update_weight();
	rules.push_back(MoveRules);

	// IN AIR Rules
	ProductionSet AirRules;
	AirRules.lhs_label = HyperedgeLabel::IN_AIR;
	{
		Production air_1(HyperedgeLabel::IN_AIR, 1);

		Node ns[2];
		ns[0].set_name("n0");
		ns[1].set_name("n1");

		Edge e(EdgeLabel::kick, "e0", "n0", "n1");

		ns[0].add_source_edge("e0");
		ns[1].add_target_edge("e0");

		air_1.replacement_graph.add_nodes(2, ns);
		air_1.replacement_graph.add_edge(e);

		air_1.replacement_graph.add_external_node("n0");
		air_1.replacement_graph.add_external_node("n1");

		AirRules.AddRule(air_1);

	}
	{

		Production air_2(HyperedgeLabel::IN_AIR, 2);

		Node ns[3];
		ns[0].set_name("n0");
		ns[1].set_name("n1");
		ns[2].set_name("n2");

		Edge e(EdgeLabel::kick, "e0", "n0", "n1");

		Hyperedge h("h0", HyperedgeLabel::KICKING);
		h.add_attachment_node("n1");
		h.add_attachment_node("n2");

		ns[0].add_source_edge("e0");
		ns[1].add_target_edge("e0");

		ns[1].add_hyperedge("h0");
		ns[2].add_hyperedge("h0");

		air_2.replacement_graph.add_nodes(3, ns);
		air_2.replacement_graph.add_edge(e);
		air_2.replacement_graph.add_hyperedge(h);

		air_2.replacement_graph.add_external_node("n0");
		air_2.replacement_graph.add_external_node("n2");

		AirRules.AddRule(air_2);


	}
	{
		Production air_3(HyperedgeLabel::IN_AIR, 1);

		Node ns[2];
		ns[0].set_name("n0");
		ns[1].set_name("n1");

		Edge e(EdgeLabel::dive, "e0", "n0", "n1");

		ns[0].add_source_edge("e0");
		ns[1].add_target_edge("e0");

		air_3.replacement_graph.add_nodes(2, ns);
		air_3.replacement_graph.add_edge(e);

		air_3.replacement_graph.add_external_node("n0");
		air_3.replacement_graph.add_external_node("n1");

		AirRules.AddRule(air_3);

	}
	{

		Production air_4(HyperedgeLabel::IN_AIR, 2);

		Node ns[3];
		ns[0].set_name("n0");
		ns[1].set_name("n1");
		ns[2].set_name("n2");

		Edge e(EdgeLabel::dive, "e0", "n0", "n1");

		Hyperedge h("h0", HyperedgeLabel::DIVING);
		h.add_attachment_node("n1");
		h.add_attachment_node("n2");

		ns[0].add_source_edge("e0");
		ns[1].add_target_edge("e0");

		ns[1].add_hyperedge("h0");
		ns[2].add_hyperedge("h0");

		air_4.replacement_graph.add_nodes(3, ns);
		air_4.replacement_graph.add_edge(e);
		air_4.replacement_graph.add_hyperedge(h);

		air_4.replacement_graph.add_external_node("n0");
		air_4.replacement_graph.add_external_node("n2");

		AirRules.AddRule(air_4);

	}
	AirRules.update_weight();
	rules.push_back(AirRules);

	// KICKING Rules
	ProductionSet KickingRules;
	KickingRules.lhs_label = HyperedgeLabel::KICKING;
	{
		Production kick_1(HyperedgeLabel::KICKING, 1);

		Node ns[2];
		ns[0].set_name("n0");
		ns[1].set_name("n1");

		Edge e(EdgeLabel::dive, "e0", "n0", "n1");

		ns[0].add_source_edge("e0");
		ns[1].add_target_edge("e0");

		kick_1.replacement_graph.add_nodes(2, ns);
		kick_1.replacement_graph.add_edge(e);

		kick_1.replacement_graph.add_external_node("n0");
		kick_1.replacement_graph.add_external_node("n1");

		KickingRules.AddRule(kick_1);

	}
	{

		Production kick_2(HyperedgeLabel::KICKING, 2);

		Node ns[3];
		ns[0].set_name("n0");
		ns[1].set_name("n1");
		ns[2].set_name("n2");

		Edge e(EdgeLabel::dive, "e0", "n0", "n1");

		Hyperedge h("h0", HyperedgeLabel::DIVING);
		h.add_attachment_node("n1");
		h.add_attachment_node("n2");

		ns[0].add_source_edge("e0");
		ns[1].add_target_edge("e0");

		ns[1].add_hyperedge("h0");
		ns[2].add_hyperedge("h0");

		kick_2.replacement_graph.add_nodes(3, ns);
		kick_2.replacement_graph.add_edge(e);
		kick_2.replacement_graph.add_hyperedge(h);

		kick_2.replacement_graph.add_external_node("n0");
		kick_2.replacement_graph.add_external_node("n2");

		KickingRules.AddRule(kick_2);


	}
	{
		Production kick_3(HyperedgeLabel::KICKING, 1);

		Node ns[2];
		ns[0].set_name("n0");
		ns[1].set_name("n1");

		Edge e(EdgeLabel::deflect, "e0", "n0", "n1");

		ns[0].add_source_edge("e0");
		ns[1].add_target_edge("e0");

		kick_3.replacement_graph.add_nodes(2, ns);
		kick_3.replacement_graph.add_edge(e);

		kick_3.replacement_graph.add_external_node("n0");
		kick_3.replacement_graph.add_external_node("n1");

		KickingRules.AddRule(kick_3);

	}
	{

		Production kick_4(HyperedgeLabel::KICKING, 2);

		Node ns[3];
		ns[0].set_name("n0");
		ns[1].set_name("n1");
		ns[2].set_name("n2");

		Edge e(EdgeLabel::deflect, "e0", "n0", "n1");

		Hyperedge h("h0", HyperedgeLabel::IN_AIR);
		h.add_attachment_node("n1");
		h.add_attachment_node("n2");

		ns[0].add_source_edge("e0");
		ns[1].add_target_edge("e0");

		ns[1].add_hyperedge("h0");
		ns[2].add_hyperedge("h0");

		kick_4.replacement_graph.add_nodes(3, ns);
		kick_4.replacement_graph.add_edge(e);
		kick_4.replacement_graph.add_hyperedge(h);

		kick_4.replacement_graph.add_external_node("n0");
		kick_4.replacement_graph.add_external_node("n2");

		KickingRules.AddRule(kick_4);

	}
	KickingRules.update_weight();
	rules.push_back(KickingRules);

	// DIVING Rules

	ProductionSet DivingRules;
	DivingRules.lhs_label = HyperedgeLabel::DIVING;
	{
		Production dive_1(HyperedgeLabel::DIVING, 1);

		Node ns[2];
		ns[0].set_name("n0");
		ns[1].set_name("n1");

		Edge e(EdgeLabel::backflip, "e0", "n0", "n1");

		ns[0].add_source_edge("e0");
		ns[1].add_target_edge("e0");

		dive_1.replacement_graph.add_nodes(2, ns);
		dive_1.replacement_graph.add_edge(e);

		dive_1.replacement_graph.add_external_node("n0");
		dive_1.replacement_graph.add_external_node("n1");

		DivingRules.AddRule(dive_1);

	}
	{

		Production dive_2(HyperedgeLabel::DIVING, 2);

		Node ns[3];
		ns[0].set_name("n0");
		ns[1].set_name("n1");
		ns[2].set_name("n2");

		Edge e(EdgeLabel::backflip, "e0", "n0", "n1");

		Hyperedge h("h0", HyperedgeLabel::IN_AIR);
		h.add_attachment_node("n1");
		h.add_attachment_node("n2");

		ns[0].add_source_edge("e0");
		ns[1].add_target_edge("e0");

		ns[1].add_hyperedge("h0");
		ns[2].add_hyperedge("h0");

		dive_2.replacement_graph.add_nodes(3, ns);
		dive_2.replacement_graph.add_edge(e);
		dive_2.replacement_graph.add_hyperedge(h);

		dive_2.replacement_graph.add_external_node("n0");
		dive_2.replacement_graph.add_external_node("n2");

		DivingRules.AddRule(dive_2);


	}
	{
		Production dive_3(HyperedgeLabel::DIVING, 1);

		Node ns[2];
		ns[0].set_name("n0");
		ns[1].set_name("n1");

		Edge e(EdgeLabel::dive_spring, "e0", "n0", "n1");

		ns[0].add_source_edge("e0");
		ns[1].add_target_edge("e0");

		dive_3.replacement_graph.add_nodes(2, ns);
		dive_3.replacement_graph.add_edge(e);

		dive_3.replacement_graph.add_external_node("n0");
		dive_3.replacement_graph.add_external_node("n1");

		DivingRules.AddRule(dive_3);

	}
	{

		Production dive_4(HyperedgeLabel::DIVING, 2);

		Node ns[3];
		ns[0].set_name("n0");
		ns[1].set_name("n1");
		ns[2].set_name("n2");

		Edge e(EdgeLabel::dive_spring, "e0", "n0", "n1");

		Hyperedge h("h0", HyperedgeLabel::IN_AIR);
		h.add_attachment_node("n1");
		h.add_attachment_node("n2");

		ns[0].add_source_edge("e0");
		ns[1].add_target_edge("e0");

		ns[1].add_hyperedge("h0");
		ns[2].add_hyperedge("h0");

		dive_4.replacement_graph.add_nodes(3, ns);
		dive_4.replacement_graph.add_edge(e);
		dive_4.replacement_graph.add_hyperedge(h);

		dive_4.replacement_graph.add_external_node("n0");
		dive_4.replacement_graph.add_external_node("n2");

		DivingRules.AddRule(dive_4);

	}
	DivingRules.update_weight();
	rules.push_back(DivingRules);



}

void HyperEdgeGrammar::reset_graph()
{
	level_graph.clear_graph();
	make_starting_graph();
	replacement_count = 0;
}



void HyperEdgeGrammar::generate_graph(GLFWwindow* window)
{

	if (level_graph.do_hyperedges_remain())
	{
		char pre = 'a' + replacement_count;
		std::string pr;
		pr.push_back(pre);
		std::string prefix = pr + "_";
		single_replacement(window, prefix);
		replacement_count++;
	}
	

}

void HyperEdgeGrammar::single_replacement(GLFWwindow* window, std::string prefix)
{

	//select hyperedge to replace
	Hyperedge* hyperedge_to_replace = level_graph.select_hyperedge_to_replace();

	//select rule to apply
	Graph replacement_graph;
	Production* rule_applied = nullptr;
	for (int i = 0; i < rules.size(); i++)
	{
		if (rules.data()[i].lhs_label == hyperedge_to_replace->get_label())
		{
			rule_applied = rules.data()[i].select_rule_to_apply();
			replacement_graph = rule_applied->replacement_graph;

			break;
		}
	}
	if (rule_applied == nullptr)
	{
		return;
	}

	//remove hyperedge from attachment nodes
	hyperedge_to_replace->delete_from_attachment_nodes(&level_graph);

	// copy replacement graph elements to level graph
	replacement_graph.copy_elements_to_level_graph(&level_graph, prefix);

	// glue external nodes to attachment nodes
	replacement_graph.glue_nodes(&level_graph, hyperedge_to_replace);

	// remove replaced hyperedge
	level_graph.remove_hyperedge(hyperedge_to_replace->get_name());


	//copy replacement graph to clipboard
	//replacement_graph.output_dot(window);
	if (rule_applied) { rule_applied->replacement_graph.output_dot(window); }
}

void HyperEdgeGrammar::GenerateWholeGraph(GLFWwindow* window)
{
	while (level_graph.do_hyperedges_remain())
	{
		char pre = 'a' + replacement_count;
		std::string pr;
		pr.push_back(pre);
		std::string prefix = pr + "_";
		single_replacement(window, prefix);
		replacement_count++;
	}

}


void HyperEdgeGrammar::get_data(int& diff, int& vari)
{

	diff = level_graph.get_edges().size();


	std::map<EdgeLabel, bool> moves;
	moves[EdgeLabel::jump] = false;
	moves[EdgeLabel::long_jump] = false;
	moves[EdgeLabel::backflip] = false;
	moves[EdgeLabel::dive] = false;
	moves[EdgeLabel::dive_spring] = false;
	moves[EdgeLabel::kick] = false;
	moves[EdgeLabel::deflect] = false;


	for (auto& e : level_graph.get_edges())
	{
		moves[e.second.get_label()] = true;
	}

	vari = 0;
	for (auto& move : moves)
	{
		if (move.second)
		{
			vari += 1;
		}
	}

}

void HyperEdgeGrammar::get_dist(int& num, int& jumps, int& ljumps, int& bflips, int& dives, int& dsprings, int& kicks, int& deflects)
{

	num += level_graph.get_edges().size();


	std::map<EdgeLabel, int> moves;
	moves[EdgeLabel::jump] = 0;
	moves[EdgeLabel::long_jump] = 0;
	moves[EdgeLabel::backflip] = 0;
	moves[EdgeLabel::dive] = 0;
	moves[EdgeLabel::dive_spring] = 0;
	moves[EdgeLabel::kick] = 0;
	moves[EdgeLabel::deflect] = 0;


	for (auto& e : level_graph.get_edges())
	{
		moves[e.second.get_label()] += 1;
	}

	jumps += moves[EdgeLabel::jump];
	ljumps += moves[EdgeLabel::long_jump];
	bflips += moves[EdgeLabel::backflip];
	dives += moves[EdgeLabel::dive];
	dsprings += moves[EdgeLabel::dive_spring];
	kicks += moves[EdgeLabel::kick];
	deflects += moves[EdgeLabel::deflect];


}

Graph HyperEdgeGrammar::get_output_graph()
{
	return level_graph;
}

void HyperEdgeGrammar::copy_current_graph(GLFWwindow* window)
{
	level_graph.output_dot(window);
}

