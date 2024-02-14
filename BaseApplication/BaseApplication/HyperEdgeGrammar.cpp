#include "HyperEdgeGrammar.h"

#include <iostream>

#include <stack>

// ------ NODE FUNCTIONS -------------

void Node::remove_hyperedge(const std::string& name)
{
	hyperedges.erase(name);
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

	// copy hyperedges to node
	for (std::string h : hyperedges)
	{
		Hyperedge* hptr = level_graph->get_hyperedge_from_name(h);
		hptr->update_node_name(name, new_name);
	}

	// copy source edges to node
	for (std::string es : edges_source)
	{
		Edge* esptr = level_graph->get_edge_from_name(es);
		esptr->update_source_name(new_name);
	}

	// copy target edges to node
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


// ------ GRAPH FUNCTIONS ------------

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
	edges[e.name] = e;
}

void Graph::add_hyperedge(Hyperedge& h)
{
	hyperedges[h.name] = h;		
}

void Graph::add_node(Node& n)
{
	nodes[n.name] = n;
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
	for (auto n : nodes)
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
	for (auto e : edges)
	{
		e.second.update_names(prefix);
		level_graph->add_edge(e.second);
	}

	//	hyperedges
	for (auto h : hyperedges)
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


// ------ PRODUCTION FUNCTIONS -------

Graph* ProductionSet::select_rule_to_apply()
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
			return &productions.data()[i].replacement_graph;
		}

	}
	return &productions.data()[0].replacement_graph;


}


// ------ GRAMMAR FUNCTIONS ----------


HyperEdgeGrammar::HyperEdgeGrammar()
{

}

HyperEdgeGrammar::~HyperEdgeGrammar()
{


}



void HyperEdgeGrammar::generate_graph()
{

	if (level_graph.do_hyperedges_remain())
	{
		single_replacement(std::to_string(replacement_count));
		replacement_count++;
	}


}

void HyperEdgeGrammar::single_replacement(std::string prefix)
{

	//select hyperedge to replace
	Hyperedge* hyperedge_to_replace = level_graph.select_hyperedge_to_replace();

	//select rule to apply
	Graph* replacement_graph = nullptr;
	for (int i = 0; i < rules.size(); i++)
	{
		if (rules.data()[i].lhs_label == hyperedge_to_replace->label)
		{
			replacement_graph = rules.data()[i].select_rule_to_apply();
			break;
		}
	}
	if (replacement_graph == nullptr)
	{
		return;
	}

	//remove hyperedge from attachment nodes
	hyperedge_to_replace->delete_from_attachment_nodes(&level_graph);

	// copy replacement graph elements to level graph
	replacement_graph->copy_elements_to_level_graph(&level_graph, prefix);

	// glue external nodes to attachment nodes
	replacement_graph->glue_nodes(&level_graph, hyperedge_to_replace);

	// remove replaced hyperedge
	level_graph.remove_hyperedge(hyperedge_to_replace->name);

}


Graph HyperEdgeGrammar::get_output_graph()
{
	return level_graph;
}


void HyperEdgeGrammar::output_dot()
{











}