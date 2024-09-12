#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include "cache.hpp"

int cache_t::create_cache_node(int key) {

    if (frequency_list.size() == 0 or frequency_list.begin()->frequency != 1) {
        create_frequency_node(1, frequency_list.begin());
    }

    cache_node node = {key, 1, frequency_list.begin()};

    frequency_list.begin()->cache_nodes.push_front(node);

    cache_hash_table[key] = frequency_list.begin()->cache_nodes.begin();

    return 0;
}

std::list<frequency_node>::iterator cache_t::create_frequency_node(size_t frequency,
                                   std::list<frequency_node>::iterator position) {
    frequency_node node = {frequency, {}};
    
    return frequency_list.insert(position, node);;
}

int cache_t::add_cache(int key) {
    create_cache_node(key);

    cache_node_it node = cache_hash_table[key];

    size_t frequency_list_head_value = frequency_list.begin()->frequency;

    if (frequency_list_head_value != 1) {
        create_frequency_node(1, frequency_list.begin());
    }

    node->freq_node = frequency_list.begin();

    return 0;
}
 
int cache_t::delete_least_used() {
    if (frequency_list.size() != 0 and frequency_list.begin()->cache_nodes.size() != 0) {
        int key = frequency_list.begin()->cache_nodes.back().index;
        frequency_list.begin()->cache_nodes.pop_back();
        cache_hash_table.erase(key);
    }

    if (frequency_list.size() != 0 and frequency_list.begin()->cache_nodes.size() == 0) {
        frequency_list.pop_front();
    }
    return 0;
}

bool cache_t::full() const{
    if (cache_size == cache_hash_table.size()) {
        return true;
    }
    return false;
} 

bool cache_t::empty() const{
    if (cache_hash_table.size() == 0) {
        return true;
    }
    return false;
} 

bool cache_t::lookup_update(int key) {
    //std::cout<<key<<std::endl;
    //std::cout << "entered lookup_update\n";
    //print_hash_table();
    //print_frequency_list();
    //std::cout << "\nexited lookup_update\n";

    auto hit = cache_hash_table.find(key);

    if (full()) {
        if (hit == cache_hash_table.end()) {
            delete_least_used();    
        }
    }

    if (hit == cache_hash_table.end()) {
        add_cache(key);
        return false;
    }  

    size_t new_frequency = hit->second->freq_node->frequency + 1;
    freq_node_it prev_freq_node = hit->second->freq_node;
    freq_node_it next_freq_node = prev_freq_node;
    next_freq_node++;

    if (new_frequency != next_freq_node->frequency) {
        next_freq_node = create_frequency_node(new_frequency, next_freq_node);
    }
    
    prev_freq_node->cache_nodes.erase(hit->second);

    if (prev_freq_node->cache_nodes.size() == 0) {
        frequency_list.erase(prev_freq_node);
    }

    next_freq_node->cache_nodes.push_front(*hit->second);
    cache_hash_table[key] = next_freq_node->cache_nodes.begin();
    cache_hash_table[key]->freq_node = next_freq_node;


    hit->second->frequency++;
    hits++;

    return true;
}

int cache_t::read_input_pages(std::vector<int>* list) {
    int buf = 0;
    for (int i = 0; i < pages_amount; i++) {
        std::cin >> buf;
        list->push_back(buf);
    }
    return 0;
}

int cache_t::print_hash_table() const {
    std::cout << "Hash table:\n";
    std::cout << "[";
    for (auto element = cache_hash_table.begin(); element != cache_hash_table.end(); element++) {
        std::cout << "{" << element->first << ", {" << element->second->index << ", "
        << element->second->frequency << "}}";
        if (++cache_hash_table.find(element->first) != cache_hash_table.end()) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << '\n';
    return 0;
}

int cache_t::print_frequency_list() const {
    std::cout << "Frequency list:\n";
    std::cout << "[";
    for (auto element = frequency_list.begin(); element != frequency_list.end(); element++) {
        std::cout << "{" << element->frequency << ", ";
        print_cache_nodes_list(element->cache_nodes);
        std::cout << "}";
        if (element->frequency != (--frequency_list.end())->frequency) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << '\n';
    return 0;
}
int cache_t::print_cache_nodes_list(const std::list<cache_node> list) const {
    std::cout << "[";
    for (auto element = list.begin(); element != list.end(); element++) {
        std::cout << element->index;
        if (element != --list.end()) {
            std::cout << ", ";
        }
    }
    std::cout << "]";
    return 0;
}

int main() {
    size_t cache_size, pages_amount, a, b;
    std::vector<int> pages_list;

    std::cin >> cache_size >> pages_amount >> a >> b;

    cache_t cache(cache_size, pages_amount);

    cache.read_input_pages(&pages_list);
    int count = 0;
    for (auto i : pages_list) {
        cache.lookup_update(i);
        //cache.print_hash_table();
        //cache.print_frequency_list();
        //std::cout << "--------------------------------------\n";

    }   
    std::cout << cache.hits << std::endl;
}
