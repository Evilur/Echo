window.onerror = function(message, source, lineno, colno, error) {
    console.error("Uncaught error:", message, "at", source + ":" + lineno);
};

console.log = (...args) => { document.body.innerHTML += 'Penis'; }
console.warn = (...args) => { document.body.innerHTML += 'Penis'; }
console.error = (...args) => { document.body.innerHTML += 'Penis'; }