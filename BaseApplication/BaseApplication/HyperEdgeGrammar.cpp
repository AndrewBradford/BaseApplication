#include "HyperEdgeGrammar.h"

#include <iostream>


HyperEdgeGrammar::HyperEdgeGrammar()
{

}

HyperEdgeGrammar::~HyperEdgeGrammar()
{

}





void HyperEdgeGrammar::single_transformation()
{


	// identify hyperedge to be replaced
	Hyperedge* hyperedge_to_replace = graph.get_next_hyperedge_to_transform();


	// identify production rule to apply
	 
	//		find production set for the hyperedge's label
	int production_set = -1;
	for (int i = 0; i < rules.size(); i++)
	{
		if (rules[i].lhs_label == hyperedge_to_replace->label)
		{
			production_set = i;
			break;
		}
	}
	if (production_set == -1)
	{
		//no production set that matches the label
		std::cout << "no rule matches hyperedge\n";
		return;
	}

	//		get the production rule that should be applied 
	Production* rule_to_apply = rules[production_set].select_rule_to_apply();



	//		remove references to hyperedge from attached nodes
	for (Node* n : hyperedge_to_replace->attachment_nodes_ptrs)
	{
		n->remove_hyperedge(hyperedge_to_replace->id);
	}


	//		attach subgraph of production to graph
	subGraph* replacing_structure = &rule_to_apply->rhs;

	
	GraphMapping graph_map;
	
	//			map each node in subgraph to new node in graph
	for (Node& n : replacing_structure->nodes)
	{
		bool is_external = false;
		for (int i = 0; i < replacing_structure->external_nodes.size(); i++)
		{
			// external nodes should be mapped to corresponding attachment node
			if (replacing_structure->external_nodes[i] == &n)
			{
				int external_number = i;
				// find corresponding attachment node graph id
				graph_map.node_map[&n] = hyperedge_to_replace->attachment_nodes_ptrs[external_number];

				is_external = true;
			}
		}
		if (is_external) { continue; }

		graph.nodes.push_back(n);
		graph_map.node_map[&n] = &graph.nodes.back();

	}

	//			map each edge and hyperedge in subgraph to new one in graph
	for (Edge& e : replacing_structure->edges)
	{

		graph.edges.push_back(e);
		graph_map.edge_map[&e] = &graph.edges.back();

	}

	for (Hyperedge& h : replacing_structure->hyperedges)
	{

		graph.hyperedges.push_back(h);
		graph_map.hyperedge_map[&h] = &graph.hyperedges.back();


	}

	//			pass over each node, edge and hyperedge again
	//			replace each pointer with the mapped pointer
	for (Node& n : replacing_structure->nodes)
	{
		for (Edge*& e : n.edges_source_ptrs)
		{
			e = graph_map.edge_map[e];
		}

		for (Edge*& e : n.edges_target_ptrs)
		{
			e = graph_map.edge_map[e];
		}

		for (Hyperedge*& h : n.hyperedges_ptrs)
		{
			h = graph_map.hyperedge_map[h];
		}

	}

	for (Edge& e : replacing_structure->edges)
	{
		e.source_node_ptr = graph_map.node_map[e.source_node_ptr];
		e.target_node_ptr = graph_map.node_map[e.target_node_ptr];
	}

	for (Hyperedge& h : replacing_structure->hyperedges)
	{
		for (Node*& n : h.attachment_nodes_ptrs)
		{
			n = graph_map.node_map[n];
		}
	}


	//		delete hyperedge
	graph.remove_hyperedge(hyperedge_to_replace->id);



}






void HyperEdgeGrammar::draw_graph(GraphDisplay& display)
{



	






}

void HyperEdgeGrammar::output_dot()
{











}