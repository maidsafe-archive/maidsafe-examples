var path = require("path");

module.exports = function (grunt) {
    grunt.loadNpmTasks('grunt-gitbook');
    grunt.loadNpmTasks('grunt-gh-pages');
    grunt.loadNpmTasks('grunt-contrib-clean');
    grunt.loadNpmTasks('grunt-string-replace');

    grunt.initConfig({
        'gitbook': {
            development: {
                input: "./",
                github: "maidsafe/maidsafe-examples"
            }
        },
        'gh-pages': {
            options: {
                base: '_book'
            },
            src: ['**']
        },
        'clean': {
            files: ['.grunt' , '_book']
        },
        'string-replace': {
          dist: {
            files: {
              '_book/': '_book/**/style.css'
            },
            options: {
              replacements: [{
                pattern: '.book .book-body .navigation.navigation-next{right:0',
                replacement: '.book .book-body .navigation.navigation-next{right:15px'
              }]
            }
          }
        }
    });

    grunt.registerTask('publish', [
      'gitbook',
      'string-replace',
      'gh-pages',
      'clean'
    ]);

    grunt.registerTask('default', [
      'gitbook',
      'string-replace'
    ]);
};