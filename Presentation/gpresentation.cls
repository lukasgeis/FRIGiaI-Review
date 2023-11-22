\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{gpresentation}[2023/07/17]

\DeclareOption*{\PassOptionsToClass{\CurrentOption}{beamer}}
\ProcessOptions\relax
\LoadClass[xcolor=dvipsnames, t]{beamer}

%%% Checks whether a string is not given/empty/blank or not.
% Ex.: \NewDocumentCommand{\test}{O{}}{\IfEmptyTF{#1}{true}{false}}
% \test -> true
% \test[] -> true
% \test[   ] -> true
% \test[a] -> false
\ExplSyntaxOn
\cs_set_eq:NN\IfEmptyT\tl_if_blank:nT
\cs_set_eq:NN\IfEmptyF\tl_if_blank:nF
\cs_set_eq:NN\IfEmptyTF\tl_if_blank:nTF
\ExplSyntaxOff

\input{presentation.sty}

\RequirePackage[english]{babel}
\RequirePackage{geometry}
\RequirePackage{csquotes}
\PassOptionsToPackage{dvipsnames}{xcolor}

\RequirePackage{amsmath, amssymb, amsfonts, amsthm, mathtools}

\RequirePackage{tikz}
\RequirePackage{tikzpagenodes}
\usetikzlibrary{positioning, calc}
\RequirePackage{pgfplots}
\pgfplotsset{compat=1.18}

\RequirePackage[vlined,ruled,linesnumbered]{algorithm2e}

\definecolor{GoetheBlue}{rgb}{0,0.38,0.56}
\RequirePackage{hyperref}
\hypersetup{final}

\RequirePackage[backend=biber, style=numeric-comp, sortcites]{biblatex}
\bibliography{refs}
