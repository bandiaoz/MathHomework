function<int(int, int, int, bool)> alpha_beta = [&](int u, int alpha, int beta, bool is_max) {
    if (g[u].size() == 0) {
        return val[u];
    }
    for (auto v : g[u]) {
        if (is_max) {
            alpha = max(alpha, alpha_beta(v, alpha, beta, is_max ^ 1));
        } else {
            beta = min(beta, alpha_beta(v, alpha, beta, is_max ^ 1));
        }
        if (alpha >= beta) {
            break;
        }
    }
    
    return val[u] = is_max ? alpha : beta;
};  