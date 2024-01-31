#!/usr/bin/env node --experimental-fetch
//----------------------------------------------------------------------------//
// Finds a recent contest that has not been solved and opens it in browser    //
// Configuration:                                                             //
let PROBLEM_WANTED = "D";
//----------------------------------------------------------------------------//

import { exec } from "child_process";

let fetchretryjson = async (url, retries = 5) => {
  try {
    let resp = await (await fetch(url)).json();
    return resp;
  } catch (e) {
    if (retries == 0) {
      throw e;
    }
    await new Promise((resolve) => setTimeout(resolve, 1000));
    return await fetchretryjson(url, retries - 1);
  }
};

// get list of all contests
let contests = await fetchretryjson(
  "https://codeforces.com/api/contest.list?gym=false"
);

// sort contests by most recent
contests["result"].sort(
  (a, b) => b["startTimeSeconds"] - a["startTimeSeconds"]
);

// find a suitable contest
for (let contest of contests["result"]) {
  let contest_name = contest["name"];
  let contest_id = contest["id"];

  // check if contest is div2
  if (contest_name.includes("Div. 2") && !contest_name.includes("Div. 1")) {
    // retrieve my results from contest
    let myresults = await fetchretryjson(
      `https://codeforces.com/api/contest.status?contestId=${contest_id}&handle=danielsudz`
    );

    let solved_problem = false;
    for (let submission of myresults["result"]) {
      let problem = submission["problem"]["index"];
      let verdict = submission["verdict"];

      if (problem == PROBLEM_WANTED && verdict == "OK") {
        solved_problem = true;
        break;
      }
    }
    if (!solved_problem) {
      let contest_url = `https://codeforces.com/contest/${contest_id}/problem/${PROBLEM_WANTED}`;
      console.log(contest_url);
      // open in browser
      exec(`open ${contest_url}`);
      break;
    }
  }
}
