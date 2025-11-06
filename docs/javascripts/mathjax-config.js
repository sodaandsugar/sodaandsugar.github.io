window.MathJax = {
  tex: {
    inlineMath: [['\\(', '\\)']],
    displayMath: [['$$', '$$'], ['\\[', '\\]']],
    processEscapes: true,
    packages: {'[+]': ['ams', 'boldsymbol']} // 确保加载ams等宏包
  },
  options: {
    skipHtmlTags: ['script', 'noscript', 'style', 'textarea', 'pre'],
    ignoreHtmlClass: 'tex2jax_ignore',
    processHtmlClass: 'arithmatex'
  }
};

// 解决开发服务器实时重载时公式不重新渲染的问题
if (typeof window.MkDocsMaterial !== 'undefined') {
  document$.subscribe(() => {
    if (window.MathJax && window.MathJax.typesetPromise) {
      window.MathJax.typesetPromise();
    }
  });
}