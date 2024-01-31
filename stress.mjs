import { execSync } from "node:child_process";
import { exit } from "node:process";

let INPUT_PROG = "./out/pD";
let VALIDATE_PROG = "./out/pE";

// include random int on range [min, max]
// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math/random
let rand_int = (min, max) => Math.floor(Math.random() * (max - min + 1) + min);

// return program input here
let gen = () => {
  let N = 1e4;
  let Q = 1e4;
  let result = "1\n\n" + `${N + 1} ${Q}` + "\n" + "1 1" + "\n";
  let maxloc = 1;
  for (let i = 0; i < N; i++) {
    let type = rand_int(1, 2);
    let amount = rand_int(1, 4);
    result += String(type) + " " + String(amount) + "\n";
    if (type == 1) {
      maxloc++;
    } else {
      maxloc *= amount + 1;
    }
  }
  for (let i = 0; i < Q; i++) {
    result += String(rand_int(1, Math.min(maxloc, 1e18))) + " ";
  }
  return result;
};

let validate = (input_result, validate_result) => {
  input_result = input_result
    .replace(/\n/g, "")
    .split("\n")
    .map((item) => parseInt(item))
    .filter((x) => !isNaN(x));

  validate_result = validate_result
    .replace(/\n/g, "")
    .split("\n")
    .map((item) => parseInt(item))
    .filter((x) => !isNaN(x));

  if (input_result.length != validate_result.length) return false;
  if (input_result[0] != validate_result[0]) return false;
  return true;
};

let main = () => {
  let gen_input = gen();

  console.log(gen_input);

  let input_result = execSync(INPUT_PROG, {
    input: gen_input,
  }).toString();

  console.log(input_result);

  let validate_result = execSync(VALIDATE_PROG, {
    input: gen_input,
  }).toString();

  console.log(validate_result);

  if (!validate(input_result, validate_result)) {
    console.error("VALIDATION FAILED, INPUT BELOW:");
    console.error(gen_input);
    exit(1);
  } else {
    console.info("validation passed");
  }
};

for (let i = 0; i < 1000; i++) {
  main();
}
