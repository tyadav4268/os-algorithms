/*
Submitted By:
	Tej Pratap Yadav
	195104
*/
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

class Process{
	int arrival_time;
	int burst_time;
	int id;

	public:

	Process(int at, int bt, int id_){
		arrival_time = at;
		burst_time = bt;
		id = id_;
	}

	void print_process(){
		cout<<"Process Id: "<<id<<"\t";
		cout<<"Arrival Time: "<<arrival_time<<"\t";
		cout<<"Burst Time: "<<burst_time<<endl;
	}

	int get_arrival_time(){
		return arrival_time;
	}
	int get_burst_time(){
		return burst_time;
	}
	int get_id(){
		return id;
	}

	friend bool compare_processes(Process &a, Process &b);

};
bool compare_processes(Process &a, Process &b){
	return (a.get_burst_time() < b.get_burst_time());
}

void print_desc(queue<Process> process_queue);
void prepare_gantt_chart(queue<Process> process_queue);

void sort_process_queue(queue<Process> &process_queue){
	vector<Process> process_vector;
	while(!process_queue.empty()){
		process_vector.push_back(process_queue.front());
		process_queue.pop();
	}
	sort(process_vector.begin() + 1, process_vector.end(), compare_processes);
	for(int i = 0; i < process_vector.size(); i++){
		process_queue.push(process_vector[i]);
	}
	prepare_gantt_chart(process_queue);
}

void print_desc(queue<Process> process_queue){
	cout<<"=================================================="<<endl;
	cout<<"\tDescription of Processes"<<endl;
	int num_of_processes = process_queue.size();
	int sno = 1;
	while(num_of_processes--){
		Process process = process_queue.front();
		cout<<"\n"<<sno<<"\t";
		sno++;
		process.print_process();
		process_queue.pop();
		cout<<endl;
	}
	cout<<"================================================="<<endl;
}

void prepare_gantt_chart(queue<Process> process_queue){
	cout<<"\nAfter Job Scheduling"<<endl;
	print_desc(process_queue);
	cout<<"\n\tGantt Chart\n";
	float total_turnaround_time = 0;;
	float total_waiting_time = 0;
	int process_start_time = 0;
	int process_finish_time = 0;
	int num_of_processes = process_queue.size();
	for(int i = 0; i < num_of_processes; i++){
		Process process = process_queue.front();
		cout<<"Process Id: "<<process.get_id()<<endl;
		cout<<"Started at: "<<process_start_time<<endl;
		process_finish_time += process.get_burst_time();
		cout<<"finished at: "<<process_finish_time<<endl;
		total_turnaround_time += process_finish_time - process.get_arrival_time();
		total_waiting_time += (process_finish_time - process.get_arrival_time()) - process.get_burst_time();
		process_start_time = process_finish_time;
		process_queue.pop();
		cout<<endl;
	}
	cout<<"\nAvg Turnaround Time = "<<total_turnaround_time/num_of_processes;
	cout<<"\nAvg Waiting Time = "<<total_waiting_time/num_of_processes<<endl;
}

void shortest_job_first(){
	cout<<"Enter Number of Processes: ";
	int num_of_processes;
	cin>>num_of_processes;
	queue<Process> process_queue;
	int num_of_process = 0;
	while(num_of_process < num_of_processes){
		cout<<"\nEnter Arrival Time of Process "<<num_of_process + 1<<": ";
		int at;
		cin>>at;
		cout<<"Enter Burst Time of Process "<<num_of_process + 1<<": ";
		int bt;
		cin>>bt;
		cout<<endl;
		int id = num_of_process;
		Process process(at, bt, id);
		process_queue.push(process);
		num_of_process++;
	}
	print_desc(process_queue);
	sort_process_queue(process_queue);

}


int main(){
	cout<<"Shortest Job First\n";
	cout<<"--------------------------"<<endl;
	shortest_job_first();
}
