#pragma once

#include <opencv2/core.hpp>

namespace gui {

    struct ImProcConfig
    {
        int live_threshold;
        int binary_threshold;
        int identification_threshold;
        int max_live_th;
        int min_live_th;
        int max_bin_th;
        int min_bin_th;
        int max_ident_th;
        int min_ident_th;
        int max_sim_runs;
        int min_sim_runs;
        int nr_sim_runs;

        ImProcConfig(): 
        live_threshold(140), binary_threshold(140), identification_threshold(140), max_live_th(255),
        min_live_th(0), max_bin_th(255), min_bin_th(0), max_ident_th(255), min_ident_th(0),
        max_sim_runs(100000), min_sim_runs(0), nr_sim_runs(10000)           
        {};
        ~ImProcConfig(){};

        // Using default copy and move constructors. 
        ImProcConfig(const ImProcConfig& other) = default;	
        ImProcConfig& operator=(const ImProcConfig& other) = default;
        ImProcConfig(ImProcConfig&& other) noexcept = default;
        ImProcConfig& operator=(ImProcConfig&& other) noexcept = default;
    };
}//end namespace gui