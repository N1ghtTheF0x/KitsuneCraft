import { writeFileSync, readFileSync, existsSync, mkdirSync, statSync } from "node:fs"
import { EOL } from "node:os"
import { resolve, dirname, basename, extname } from "node:path"

const file = process.argv[2]
const output = process.argv[3] ?? file.replace(extname(file),".hpp")

const name = basename(output,extname(output))

const filepath = resolve(process.cwd(),file)
if(!existsSync(filepath))
    throw new Error(`${file} does not exist!`)
const outputpath = resolve(process.cwd(),output)
if(!existsSync(dirname(outputpath)))
    mkdirSync(dirname(output))

const content = readFileSync(filepath,"utf-8")

const guardStart = Buffer.from(`#ifndef ${name.toUpperCase()}_FILE_HPP\n#define ${name.toUpperCase()}_FILE_HPP\n`)
const guardEnd = Buffer.from("\n#endif")

const guard = (middle) => Buffer.concat([guardStart,middle,guardEnd])

const fileSize = Buffer.from(`\nconst unsigned long long ${name}_file_size = ${statSync(filepath).size};\n`)
const lines = content.split(EOL)
for(var i = 0;i < lines.length-1;i++)
    lines[i] = `"${lines[i]}\\n"`
lines[lines.length-1] = '"' + lines[lines.length-1] + "\\0" + '"'
console.dir(lines)
const fileContent = Buffer.from(`\nconst char* ${name}_file_data = ${lines.join("\n")};\n`)

const middle = Buffer.concat([fileSize,fileContent])

writeFileSync(outputpath,guard(middle))