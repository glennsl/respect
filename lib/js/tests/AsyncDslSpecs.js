// Generated by BUCKLESCRIPT VERSION 2.1.0, PLEASE EDIT WITH CARE
'use strict';

var Curry           = require("bs-platform/lib/js/curry.js");
var Respect         = require("../src/Respect.js");
var DslSpecs        = require("./DslSpecs.js");
var Respect_ctx     = require("../src/Respect_ctx.js");
var Respect_matcher = require("../src/Respect_matcher.js");

Curry._1(Respect.Dsl[/* Async */12][/* register */3], Curry._2(Respect.Dsl[/* Async */12][/* describe */2], "Async dsl", /* :: */[
          Curry._2(Respect.Dsl[/* Async */12][/* it */1], "Example group has metadata", (function () {
                  var grp = DslSpecs.parse(Curry._2(Respect.Dsl[/* Async */12][/* **> */0], /* tuple */[
                            "name",
                            "value"
                          ], Curry._2(Respect.Dsl[/* Async */12][/* describe */2], "Group", /* [] */0)));
                  var expected = Curry._3(Respect_ctx.ContextMap[/* add */3], "name", "value", Respect_ctx.ContextMap[/* empty */0]);
                  var partial_arg = grp[/* metadata */4];
                  return (function (param) {
                      return Respect_matcher.shoulda((function (param) {
                                    return Respect_matcher.equal(expected, param);
                                  }), partial_arg, param);
                    });
                })),
          /* [] */0
        ]));

/*  Not a pure module */
