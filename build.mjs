import {execSync} from "node:child_process"
import path from 'path';

execSync(
    'docker build --progress=plain . -t codeforces',
    {stdio: 'inherit'}
);

execSync(
    `docker run -it -v "${path.resolve()}":/codeforces --rm codeforces`,
    {stdio: 'inherit'}
);


