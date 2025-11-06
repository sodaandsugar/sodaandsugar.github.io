window.MathJax = {
  tex: {
    inlineMath: [['$', '$'], ['\\(', '\\)']],
    displayMath: [['$$', '$$'], ['\\[', '\\]']],
    processEscapes: true,
    packages: {'[+]': ['ams', 'boldsymbol']},
    tags: 'ams',
    tagSide: 'right',
    useLabelIds: true,
    multlineWidth: '85%',
    tags: 'all',
    ams: {
      multlineThickness: '2px'
    }
  },
  chtml: {
    scale: 1.1,
    displayAlign: 'center',
    displayIndent: '0em'
  },
  options: {
    skipHtmlTags: ['script', 'noscript', 'style', 'textarea', 'pre', 'code'],
    renderActions: {
      addMenu: [0, '', '']
    }
  },
  startup: {
    pageReady: function() {
      return MathJax.startup.defaultPageReady().then(function() {
        console.log('MathJax is ready with AMS extensions');
      });
    }
  },
  loader: {
    load: ['[tex]/ams', '[tex]/boldsymbol']
  }
};