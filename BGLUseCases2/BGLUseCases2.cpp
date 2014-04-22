/*
 * BGLUseCases.cpp
 *
 *  Created on: 10-Feb-2014
 *      Author: rajesh.rathod
 */
#include <boost/config.hpp>
#include <iostream>
#include <functional>
// #include <tuple>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/graph_utility.hpp>

	typedef struct
		{
			std::string NodeName;
			int NodeNum, NodeDistance;
		} Node;

	typedef struct
		{
			int Capacity, ResidualCapacity;
			int Cost;
		} Link;

	using namespace boost;

	typedef adjacency_list <listS, vecS, undirectedS, Node, Link, no_property> Net;


	int Add_Link(Net& N, int NodeNum1, int NodeNum2, Link L)
	{
	int NumVertices, i;
	typename graph_traits<Net>::vertex_iterator vi_begin, vi_end, ir;
	typename graph_traits<Net>::vertex_descriptor vx, vy;
	typename graph_traits<Net>::edge_descriptor e;

	bool flagx, flagy;

	NumVertices=num_vertices(N);
	flagx=0;
	flagy=0;

	vi_begin=vertices(N).first;
	ir=vi_begin;

	//Note: *ir is the vertex_descriptor
		for (i=0;i<NumVertices;i++)
		{
		if(N[*ir].NodeNum==NodeNum1) {vx=*ir; flagx=1;}
		if(N[*ir].NodeNum==NodeNum2) {vy=*ir; flagy=1;}
		ir++;
		}

	if(flagx && flagy)
	{
	e=add_edge(vx, vy, L, N).first;
	return(1);
	}
	else
	{
		return(0);
	}
	}


template <class GType> void my_print_graph(GType &G)
{
	typename graph_traits<GType>::vertex_descriptor vd;
	typename graph_traits<GType>::edge_descriptor ed;
	typename graph_traits<GType>::vertex_iterator vi;
	typename graph_traits<GType>::out_edge_iterator ei;
	int NumVertices, NumEdges, i, j;
	int Cost, Capacity, ResidualCapacity, From, To;

	NumVertices = num_vertices(G);
	vi=vertices(G).first;

	for(i=0; i<NumVertices; i++)
	{
		NumEdges=out_degree(*vi, G);
		ei=out_edges(*vi, G).first;
		std::cout << "Vertex No: " << G[*vi].NodeNum << "\n";
		for (j=0; j<NumEdges; j++)
		{
			Cost=G[*ei].Cost;
			Capacity=G[*ei].Capacity;
			ResidualCapacity=G[*ei].ResidualCapacity;
			From=G[source(*ei,G)].NodeNum;
			To=G[target(*ei,G)].NodeNum;
			std::cout << "From " << From << " To " << To << " Capacity " << Capacity << " Residual Capacity " << ResidualCapacity << " Cost " << Cost << std::endl;
			ei++;
		}
		vi++;
	}
}


template <typename Graph>
	int print_Node_Links(Graph& N, typename graph_traits<Graph>::vertex_descriptor v)
	{
	typename graph_traits<Graph>::out_edge_iterator e1, er;
	typename graph_traits<Graph>::edge_descriptor e;
	typename graph_traits<Graph>::vertex_descriptor vr;
	int NumEdges, i, From, To;
	int Cost, Capacity, ResidualCapacity;
	NumEdges=out_degree(v, N);
	i=NumEdges;

	er=out_edges(v, N).first;

//	std::cout << "Node Number: " << N[v].NodeNum << std::endl;

		for (i=0;i<NumEdges;i++)
		{
		Cost=N[*er].Cost;
		Capacity=N[*er].Capacity;
		ResidualCapacity=N[*er].ResidualCapacity;
		From=N[source(*er, N)].NodeNum;
		To=N[target(*er, N)].NodeNum;

		std::cout << "From: " << From << " To: " << To << " Cost: " << Cost << " Capacity: " << Capacity << " Residual Capacity: " << ResidualCapacity << std::endl;

		er++;
		}

	return(1);
}



class BandwidthCheck
{
typedef typename graph_traits<Net>::edge_descriptor Edge_Des;
int m_RBW;
Net m_N;

public:
BandwidthCheck() {m_RBW=0;}
BandwidthCheck(int BW, Net &N)
	{
	m_RBW=BW;
	m_N=N;
	std::cout << "m_RBW: " << m_RBW << std::endl;
	}
bool operator()(Edge_Des e)
	{
	std::cout << "Capacity: " << m_N[e].Capacity << " Residual Capacity: " << m_N[e].ResidualCapacity << std::endl;
	return (m_N[e].ResidualCapacity < m_RBW);
	}
};

typedef filtered_graph<Net,BandwidthCheck> FilteredNet;

/*
int print_filtered_graph (FilteredNet &G)
{
	typename graph_traits<FilteredNet>::vertex_descriptor vd;
	typename graph_traits<FilteredNet>::edge_descriptor ed;
	typename graph_traits<FilteredNet>::vertex_iterator vi;
	typename graph_traits<FilteredNet>::out_edge_iterator ei;
	int NumVertices, NumEdges, i, j;
	int Cost, Capacity, ResidualCapacity, From, To;

	NumVertices = num_vertices(G);
	vi=vertices(G).first;

	for(i=0; i<NumVertices; i++)
	{
		NumEdges=out_degree(*vi, G);
		ei=out_edges(*vi, G).first;
		std::cout << "Vertex No: " << G[*vi].NodeNum << std::endl;
		for (j=0; j<NumEdges; j++)
		{
			Cost=G[*ei].Cost;
			Capacity=G[*ei].Capacity;
			ResidualCapacity=G[*ei].ResidualCapacity;
			From=G[source(*ei,G)].NodeNum;
			To=G[target(*ei,G)].NodeNum;
			std::cout << "From " << From << " To " << To << " Capacity " << Capacity << " Residual Capacity " << ResidualCapacity << " Cost " << Cost << std::endl;
			ei++;
		}
		vi++;
	}
return 1;
}
*/

int main()
{
//	typedef std::pair<int,int> Link_t;
	typename graph_traits<Net>::vertex_descriptor x, y;
	typename graph_traits<Net>::edge_descriptor f;
	typename Net::vertex_property_type vq;
	typename graph_traits<Net>::vertex_iterator p,q;
	typename graph_traits<Net>::edge_iterator j,k;
	typename graph_traits<FilteredNet>::vertex_descriptor z;
	typename graph_traits<FilteredNet>::vertex_iterator r;

//	LinkProperty L1, L2;
//	NodeProperty N1, N2;

	std::string NodeName = "Chennai";
	int temp, temp1;
	bool flag;
	Link L1, L2;

	Net M;

//Setup the Network with 10 nodes:

	vq.NodeName="Ramanka";
	vq.NodeNum=0;

	x = add_vertex(vq, M);
	y=x;

	z=y;

	vq.NodeName="Bhavnagar";
	vq.NodeNum=1;

	x = add_vertex(vq, M);

	vq.NodeName="Ahmedabad";
	vq.NodeNum=2;

	x = add_vertex(vq, M);

	vq.NodeName="Pondichery";
	vq.NodeNum=3;

	x = add_vertex(vq, M);


	vq.NodeName="Vadodara";
	vq.NodeNum=4;

	x = add_vertex(vq, M);

	vq.NodeName="Rajkot";
	vq.NodeNum=5;

	x = add_vertex(vq, M);

	vq.NodeName="Chennai";
	vq.NodeNum=6;

	x = add_vertex(vq, M);

	vq.NodeName="Tirunelveli";
	vq.NodeNum=7;

	x = add_vertex(vq, M);

	vq.NodeName="Bangalore";
	vq.NodeNum=8;

	x = add_vertex(vq, M);

	vq.NodeName="Trichy";
	vq.NodeNum=9;

	x = add_vertex(vq, M);

	vq.NodeName="Kancheepuram";
	vq.NodeNum=10;

	x = add_vertex(vq, M);

//Setup the Links with Capacity and Cost Parameters:

	L1.Cost=4;
	L1.Capacity=25;
	L1.ResidualCapacity=25;

	temp=-1;
	L1.Cost=4;
	L1.Capacity=25;
	L1.ResidualCapacity=25;
	temp=Add_Link(M, 0, 1, L1);

	temp=-1;
	L1.Cost=1;
	L1.Capacity=25;
	L1.ResidualCapacity=25;
	temp=Add_Link(M, 0, 3, L1);

	temp=-1;
	L1.Cost=5;
	L1.Capacity=25;
	L1.ResidualCapacity=25;
	temp=Add_Link(M, 0, 2, L1);

	temp=-1;
	L1.Cost=3;
	L1.Capacity=50;
	L1.ResidualCapacity=25;
	temp=Add_Link(M, 1, 4, L1);

	temp=-1;
	L1.Cost=1;
	L1.Capacity=15;
	L1.ResidualCapacity=5;
	temp=Add_Link(M, 1, 7, L1);

	temp=-1;
	L1.Cost=2;
	L1.Capacity=50;
	L1.ResidualCapacity=25;
	temp=Add_Link(M, 2, 5, L1);

	temp=-1;
	L1.Cost=8;
	L1.Capacity=40;
	L1.ResidualCapacity=35;
	temp=Add_Link(M, 2, 4, L1);

	temp=-1;
	L1.Cost=3;
	L1.Capacity=25;
	L1.ResidualCapacity=25;
	temp=Add_Link(M, 2, 6, L1);

	temp=-1;
	L1.Cost=7;
	L1.Capacity=20;
	L1.ResidualCapacity=10;
	temp=Add_Link(M, 3, 5, L1);

	temp=-1;
	L1.Cost=1;
	L1.Capacity=20;
	L1.ResidualCapacity=5;
	temp=Add_Link(M, 4, 6, L1);

	temp=-1;
	L1.Cost=1;
	L1.Capacity=30;
	L1.ResidualCapacity=25;
	temp=Add_Link(M, 4, 9, L1);

	temp=-1;
	L1.Cost=4;
	L1.Capacity=25;
	L1.ResidualCapacity=5;
	temp=Add_Link(M, 6, 9, L1);

	temp=-1;
	L1.Cost=1;
	L1.Capacity=40;
	L1.ResidualCapacity=15;
	temp=Add_Link(M, 6, 8, L1);

	temp=-1;
	L1.Cost=2;
	L1.Capacity=10;
	L1.ResidualCapacity=2;
	temp=Add_Link(M, 5, 7, L1);

	temp=-1;
	L1.Cost=1;
	L1.Capacity=35;
	L1.ResidualCapacity=20;
	temp=Add_Link(M, 7, 8, L1);

	temp=-1;
	L1.Cost=10;
	L1.Capacity=25;
	L1.ResidualCapacity=5;
	temp=Add_Link(M, 7, 10, L1);

	temp=-1;
	L1.Cost=4;
	L1.Capacity=25;
	L1.ResidualCapacity=10;
	temp=Add_Link(M, 8, 10, L1);

	temp=-1;
	L1.Cost=1;
	L1.Capacity=20;
	L1.ResidualCapacity=20;
	temp=Add_Link(M, 9, 10, L1);

	my_print_graph(M);

// Dijkstra Shortest Path
	std::vector<graph_traits<Net>::vertex_descriptor> Pred(num_vertices(M));
	std::vector<int> D(num_vertices(M));
	dijkstra_shortest_paths(M, y, weight_map(get(&Link::Cost, M)).predecessor_map(&Pred[0]).distance_map(&D[0]));

	std::cout << "The Shortest Path Tree:" << std::endl;

	for(unsigned int i=0; i<num_vertices(M); i++)
	{

		std::cout << "Node Number: " << i << " Distance: " << D[i] <<  " Predecessor: " << Pred[i] << std::endl;
	}


	BandwidthCheck B(19, M);

	FilteredNet MFiltered(M,B);

//	print_filtered_graph(MFiltered);

	remove_edge_if(B, M);

	my_print_graph(M);

	dijkstra_shortest_paths(M, y, weight_map(get(&Link::Cost, M)).predecessor_map(&Pred[0]).distance_map(&D[0]));

	std::cout << "The Shortest Path Tree:" << std::endl;

	for(unsigned int i=0; i<num_vertices(M); i++)
	{

		std::cout << "Node Number: " << i << " Distance: " << D[i] <<  " Predecessor: " << Pred[i] << std::endl;
	}

//	dijkstra_shortest_paths(MFiltered, z, weight_map(get(&Link::Cost, MFiltered)).predecessor_map(&Pred[0]).distance_map(&D[0]));

/*	std::cout << "The Shortest Path Tree:" << std::endl;

	for(unsigned int i=0; i<num_vertices(M); i++)
	{

		std::cout << "Node Number: " << i << " Distance: " << D[i] <<  " Predecessor: " << Pred[i] << std::endl;
	}
*/

	std::cout << "Hello BGLUseCases";

//	temp=N[v].NodeNum;
//	std::cout << N[v].NodeName;
//	temp=N[0].NodeNum;
//	std::cout << N[0].NodeName;

	return 0;
}

