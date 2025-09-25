#include <stdio.h>
#include <stdlib.h>
struct Process {
int burst_time;
int priority;
};
void calculateMetrics(int n,struct Process processes[], int turnaround_time[], int waiting_time[])
{
float avg_turnaround_time = 0, avg_waiting_time = 0;
printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

for (int i = 0; i < n; i++) {
avg_turnaround_time += turnaround_time[i];
avg_waiting_time += waiting_time[i];
printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, processes[i].burst_time, processes[i].priority,
waiting_time[i], turnaround_time[i]);
}
avg_turnaround_time /= n;
avg_waiting_time /= n;
printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
printf("Average Waiting Time: %.2f\n", avg_waiting_time);
}
void FCFS(int n, struct Process processes[]) {
int turnaround_time[n], waiting_time[n];
waiting_time[0] = 0;
turnaround_time[0] = processes[0].burst_time;
for (int i = 1; i < n; i++) {
waiting_time[i] = turnaround_time[i - 1];
turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
}
calculateMetrics(n, processes, turnaround_time, waiting_time);
}
void SJF(int n, struct Process processes[]) {
for (int i = 0; i < n - 1; i++) {
for (int j = 0; j < n - i - 1; j++) {
if (processes[j].burst_time > processes[j + 1].burst_time) {
struct Process temp = processes[j];
processes[j] = processes[j + 1];
processes[j + 1] = temp;
}
}
}
int turnaround_time[n], waiting_time[n];
waiting_time[0] = 0;
turnaround_time[0] = processes[0].burst_time;
for (int i = 1; i < n; i++) {
waiting_time[i] = turnaround_time[i - 1];
turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
}
calculateMetrics(n, processes, turnaround_time, waiting_time);
}
void priorityScheduling(int n, struct Process processes[]) {
for (int i = 0; i < n - 1; i++) {
for (int j = 0; j < n - i - 1; j++) {
if (processes[j].priority > processes[j + 1].priority) {
struct Process temp = processes[j];
processes[j] = processes[j + 1];
processes[j + 1] = temp;
}
}
}
int turnaround_time[n], waiting_time[n];
waiting_time[0] = 0;
turnaround_time[0] = processes[0].burst_time;
for (int i = 1; i < n; i++) {
waiting_time[i] = turnaround_time[i - 1];
turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
}
calculateMetrics(n, processes, turnaround_time, waiting_time);
}
void roundRobin(int n, struct Process processes[], int time_quantum) {
int remaining_time[n];
int turnaround_time[n], waiting_time[n];
for (int i = 0; i < n; i++) {
remaining_time[i] = processes[i].burst_time;
}
int time = 0;
int flag = 0;
while (1) {
flag = 0;
for (int i = 0; i < n; i++) {
if (remaining_time[i] > 0) {
flag = 1;
if (remaining_time[i] > time_quantum) {
time += time_quantum;
remaining_time[i] -= time_quantum;
} else {
time += remaining_time[i];
waiting_time[i] = time - processes[i].burst_time;
remaining_time[i] = 0;
turnaround_time[i] = time;
}
}
}
if (flag == 0) {
break;
}
}
calculateMetrics(n,processes,turnaround_time, waiting_time);
}
int main() {
int n, time_quantum;
printf("Enter the number of processes: ");
scanf("%d", &n);
struct Process processes[n];
for (int i = 0; i < n; i++) {
printf("Enter burst time for process %d: ", i + 1);
scanf("%d", &processes[i].burst_time);
printf("Enter priority for process %d: ", i + 1);
scanf("%d", &processes[i].priority);
}
printf("\nFCFS Scheduling:\n");
FCFS(n, processes);
printf("\nSJF Scheduling:\n");
SJF(n, processes);
printf("\nPriority Scheduling:\n");
priorityScheduling(n, processes);
printf("\nEnter time quantum for Round Robin: ");
scanf("%d", &time_quantum);
printf("\nRound Robin Scheduling:\n");
roundRobin(n, processes, time_quantum);
return 0;
}
