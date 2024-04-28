$$

\begin{align}
[\text{prog}] &\to [\text{stmt}]^*\\ [\text{stmt}] &\to \begin{cases}
    exit([\text{expr}]); \\ set\space\text{ident} =
    [\text{expr}];
\end{cases}
\\
[\text{expr}] &\to \text{int\_lit}
\end{align}

$$