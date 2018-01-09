open Respect_callbacks;

module Async = Respect_async;

[@bs.send]
external toString : 'a => string = "";

type matchResult('a) =
  | MatchSuccess('a)
  | MatchFailure(Obj.t);

let matchSuccess = x => MatchSuccess(x) |> Async.return;
let matchFailure = x => MatchFailure(Obj.repr(x)) |> Async.return;

type async('a) = Async.t('a);

type matcher('a,'b) = {
  f: 'a => async(matchResult('b)),
  description: string
};

let createCallback = (don:doneCallback) => 
  fun 
  | MatchSuccess(_) => don() 
  | MatchFailure(_) => don(~err="Match error",());

let expect = (actual) => {
  pri actual = actual; /* avoid warning */
  pub to_ = (matcher:matcher('a,'b)) => (don: doneCallback) => {
    matcher.f(this#actual)
      |> Async.run (
        createCallback(don), 
        ~fe=(_) => don(~err="Exception occurred",()))
  }
};

let createPred = (~f : 'a => bool, ~desc : string) : matcher('a, 'a) => {
  f : (actual) => f(actual) ? matchSuccess(actual) : matchFailure(actual),
  description : desc
};

let equal = exp => createPred(
  ~f=actual => actual == exp,
  ~desc="equal " ++ toString(exp));

module type Stringable = {
  type t;
  let to_string : t => string;
};

module type StrComparable = {
  include Stringable;
  let compare: t => t => int;
};

module Make(T : StrComparable) = {
  let equal = exp => createPred(
    ~f=actual => T.compare(actual,exp) == 0,
    ~desc="equal to " ++ T.to_string(exp));

  let greaterThan = exp => createPred(
    ~f=actual => T.compare(actual,exp) > 0,
    ~desc="greater than " ++ T.to_string(exp));

  let lessThan = exp => createPred(
    ~f=actual => T.compare(actual,exp) < 0,
    ~desc="greater than " ++ T.to_string(exp));
};
