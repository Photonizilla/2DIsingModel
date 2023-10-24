# 2DIsingModel

$ d = 2 $ Ising model describes a system with Hamiltonian

$$ \beta H = - J \sum_{ \left< i,j \right> } s_is_j - h \sum_i s_i $$

where $ J > 0 $ for ferromagnets. The partition function is

$$ Z = \sum_{\{s_i\}} \exp \left( J \sum_{ \left< i,j \right> } s_is_j + h \sum_i s_i \right) . $$

Probability distribution function

$$ p(\{s_i\}) = \frac{1}{Z} \mathrm{e}^{-H(\{s_i\})}. $$

Let's investigate the expectation value of magnetic momentum $ M(\{s_i\}) = \frac{1}{N}\sum_i s_i $

$$ \left< M \right> = \frac{1}{NZ} \sum_{\{s_i\}} M(\{s_i\}) \mathrm{e}^{-H(\{s_i\})}. $$
