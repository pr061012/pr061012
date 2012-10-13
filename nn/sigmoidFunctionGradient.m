function g = sigmoidFunctionGradient(z)
    a = sigmoidFunction(z);
    g = a .* (1 - a);
end
