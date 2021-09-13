#include <algorithm>
#include <iostream>
#include <string>
#include "Dlist.h"
#include "Instr.h"
using namespace std;

template <class T>
class stack: public Dlist<T>{
public:
    void push(T *op){
        this->insertBack(op);
    }

    T *pop(){
        return this->removeBack();
    }

    stack(): Dlist<T>(){};

    ~stack()=default;
};

template <class T>
class queue: public Dlist<T>{
public:
    void enqueue(T *op){
        this->insertBack(op);
    }

    T *dequeue(){
        return this->removeFront();
    }

    queue(): Dlist<T>(){};

    ~queue()=default;
};

int main(int argc, char *argv[])
{
/// pseudo code:
///    1. initial data stack, instruction queue, memory array
///    2.
///    while(true)
///    {
///        2.1 dequeue from instruction queue
///        2.2 pop data from data stack (if HASH, break), push calculated data back to data stack, modify memory array
///        2.3 print this instruction, stack, queue and memory (if needed)
///    }
///   print stack and memory (if needed)
    bool print_every_instruction = argc==1;
    int init_stack_len=0;
    int init_queue_len=0;
    cin >> init_stack_len >> init_queue_len;
    // 1.1 initial data stack
    stack<long> data_stack;
    for (int stack_i = 0; stack_i < init_stack_len; ++stack_i) {
        int data_i;
        cin>>data_i;
        long *data_i_ptr = new long(data_i);
        data_stack.push(data_i_ptr);
    }
    // 1.2 initial instruction queue
    queue<Instr> instruction_queue;
    for (int queue_i = 0; queue_i < init_queue_len; ++queue_i) {
        Instr instruction_i{};
        cin>>instruction_i;
        auto *instruction_i_ptr=new Instr(instruction_i);
        instruction_queue.enqueue(instruction_i_ptr);
    }
    // 1.3 initial memory array
    const int ARR_SIZE=16;
    long memory_array[ARR_SIZE];
    for (long & array_i : memory_array) {
        cin>>array_i;
    }

    while (true){
        // 2.1 dequeue from instruction queue
        Instr *instruction = instruction_queue.dequeue();
        InstrName instrName = instruction->name;
        // 2.2 pop data from data stack / push calculated data back into data stack / modify memory array
        if (instrName==InstrName::ADD){
            long *a_ptr=data_stack.pop();
            long *b_ptr=data_stack.pop();
            long sum = *a_ptr + *b_ptr;
            delete a_ptr;
            delete b_ptr;
            long *sum_ptr = new long(sum);
            data_stack.push(sum_ptr);
        } else if (instrName==InstrName::NOR){
            long *a_ptr=data_stack.pop();
            long *b_ptr=data_stack.pop();
            long nor = ~(*a_ptr | *b_ptr);
            delete a_ptr;
            delete b_ptr;
            long *nor_ptr = new long(nor);
            data_stack.push(nor_ptr);
        } else if (instrName==InstrName::IFZ){
            long *zero_ptr=data_stack.pop();
            if (*zero_ptr == 0){
                for (int i = 0; i < instruction->parameter; ++i) {
                    auto *instruction_i = instruction_queue.dequeue();
                    delete instruction_i;
                }
            }
            delete zero_ptr;
        } else if (instrName==InstrName::HALT){
            delete instruction; // otherwise, HALT will not be deleted
            break;
        } else if (instrName==InstrName::LOAD){
            long *mem_loc_ptr=data_stack.pop();
            long mem_value = memory_array[*mem_loc_ptr];
            delete mem_loc_ptr;
            long *mem_value_ptr = new long(mem_value);
            data_stack.push(mem_value_ptr);
        } else if (instrName==InstrName::STORE){
            long *mem_loc_ptr = data_stack.pop();
            long *mem_value_ptr = data_stack.pop();
            memory_array[*mem_loc_ptr] = *mem_value_ptr;
            delete mem_loc_ptr;
            delete mem_value_ptr;
        } else if (instrName==InstrName::POP){
            long *pop_ptr=data_stack.pop();
            delete pop_ptr;
        } else if (instrName==InstrName::PUSHI){
            long *push_ptr = new long(instruction->parameter);
            data_stack.push(push_ptr);
        } else if (instrName==InstrName::NOOP){
        } else{
        }
        // 2.3 print if "-s"
        if (print_every_instruction){
            cout<<*instruction<<endl;
            cout<<data_stack<<endl;
            cout<<instruction_queue<<endl;
            for (long array_i : memory_array) {
                cout<<array_i<<" ";
            }
            cout<<endl;
        }
        // 2.4 delete this instruction
        delete instruction;
    }
    // print last instruction HALT if without "-s"
    if (print_every_instruction){
        cout<<"HALT"<<endl;
        cout<<data_stack<<endl;
        cout<<instruction_queue<<endl;
        for (long array_i : memory_array) {
            cout<<array_i<<" ";
        }
        cout<<endl;
    } else{
        cout<<data_stack<<endl;
        for (long array_i : memory_array) {
            cout<<array_i<<" ";
        }
        cout<<endl;
    }
    return 0;
}
