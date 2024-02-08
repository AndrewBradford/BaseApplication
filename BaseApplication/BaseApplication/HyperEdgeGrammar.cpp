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
	int hyperedge_to_replace_ID = graph.get_next_hyperedge_to_transform();
	Hyperedge* hyperedge_to_replace = graph.get_hyperedge_from_id(hyperedge_to_replace_ID);


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



	// remove references to hyperedge from attached nodes
	for (int n : hyperedge_to_replace->attachment_nodes)
	{
		graph.get_node_from_id(n)->remove_hyperedge(hyperedge_to_replace_ID);
	}


	// attach subgraph of production to graph
	subGraph* replacing_structure = &rule_to_apply->rhs;

	//		copy each (non-external) node, edge and hyperedge from subgraph into graph
				// assign each node, edge and hyperedge in subgraph a new graph id

	//		assign each subgraph node a graph id and copy into graph
	for (Node& n : replacing_structure->nodes)
	{
		bool is_external = false;
		for (int i = 0; i < replacing_structure->external_nodes.size(); i++)
		{
			// external nodes should be merged with corresponding attachment node
			if (replacing_structure->external_nodes[i] == n.sub_node_ID)
			{
				int external_number = i;
				// find corresponding attachment node graph id
				n.node_ID = hyperedge_to_replace->attachment_nodes[external_number];

				is_external = true;
			}
		}
		if (is_external) { continue; }
		n.node_ID = graph.nodes.size();
		graph.nodes.push_back(n);
	}

	//			assign each edge and hyperedge a graph id and copy into graph
	//			update ids of attached subgraph nodes to new graph ids
	for (Edge& e : replacing_structure->edges)
	{
		e.source_node_ID = replacing_structure->get_node_from_sub_id(e.source_node_sub_ID)->node_ID;
		e.target_node_ID = replacing_structure->get_node_from_sub_id(e.target_node_sub_ID)->node_ID;
		e.edge_ID = graph.edges.size();
		graph.edges.push_back(e);
	}
	for (Hyperedge& h : replacing_structure->hyperedges)
	{
		// update each attachment node id
		for (int n : h.sub_attachment_nodes)
		{
			int new_id = replacing_structure->get_node_from_sub_id(n)->node_ID;
			h.attachment_nodes.push_back(new_id);
		}

		h.hyperedge_ID = graph.next_hyperedge_id;
		graph.hyperedges.push_back(h);
		++graph.next_hyperedge_id;
	}

	/*
	//		glue each attachment node in hyperedge 
	//		to corresponding external node in subgraph
	for (int i = 0; i < hyperedge_to_replace->type; i++)
	{
		// get attachment node
		Node* attachment_node = graph.get_node_from_id(hyperedge_to_replace->attachment_nodes[i]);
		// find matching external node in subgraph
		Node* external_node = replacing_structure->get_external_node(i);

		// find edges and hyperedges which connect to that node


	}*/



	// delete hyperedge
	graph.remove_hyperedge(hyperedge_to_replace_ID);



}

