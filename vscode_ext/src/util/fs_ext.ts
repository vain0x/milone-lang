// File system operations.

import fsP from "fs/promises"
import path from "path"

export const copyDirRecursively = async (srcDir: string, destDir: string): Promise<void> => {
  await fsP.mkdir(destDir, { recursive: true })

  const files = await fsP.readdir(srcDir)
  for (const filename of files) {
    const srcFile = path.join(srcDir, filename)
    const destFile = path.join(destDir, filename)

    const stat = await fsP.lstat(srcFile)
    if (stat.isDirectory()) {
      await copyDirRecursively(srcFile, destFile)
    } else if (stat.isFile()) {
      await fsP.copyFile(srcFile, destFile)
    } else if (stat.isSymbolicLink()) {
      const target = await fsP.realpath(srcFile)
      await fsP.symlink(target, destFile)
    } else {
      console.error("warn: couldn't copy file", srcFile)
    }
  }
}

export const unlinkDirRecursively = async (dir: string): Promise<void> => {
  const files = await fsP.readdir(dir).catch((err: { code: string }) => {
    if (err.code === "ENOENT") {
      return []
    }
    throw err
  })

  for (const filename of files) {
    const filepath = path.join(dir, filename)
    const stat = await fsP.lstat(filepath)
    if (stat.isDirectory()) {
      await unlinkDirRecursively(filepath)
    } else {
      await fsP.unlink(filepath).catch(err => {
        if (err.code === "ENOENT") {
          return // OK.
        }
        throw err
      })
    }
  }

  await fsP.unlink(dir).catch(err => {
    if (err.code === "ENOENT") {
      return // OK.
    }
    throw err
  })
}
